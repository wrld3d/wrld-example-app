// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultSectionController.h"

#include <algorithm>

#include "IAppModeModel.h"
#include "ISearchResultSectionOrder.h"
#include "SearchResultItemModel.h"
#include "SwallowSearchParser.h"
#include "SwallowSearchConstants.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace View
        {
            namespace
            {
                class OrderWrapper
                {
                private:
                    ISearchResultSectionOrder& m_order;
                public:
                    OrderWrapper(ISearchResultSectionOrder& order)
                        : m_order(order)
                    {
                    }
                    
                    bool operator() (const Search::SdkModel::SearchResultModel& a, const Search::SdkModel::SearchResultModel& b)
                    {
                        return m_order(a, b);
                    }
                };
                
                inline int GetOriginalIndexForSearchResult(const std::vector<Search::SdkModel::SearchResultModel>& unorderedResults, const Search::SdkModel::SearchResultModel& result)
                {
                    std::vector<Search::SdkModel::SearchResultModel>::const_iterator it = std::find(unorderedResults.begin(), unorderedResults.end(), result);
                    
                    return static_cast<int>(std::distance(unorderedResults.begin(), it));
                }
            }

            namespace
            {
                std::string GetMeetingRoomAvailablityIcon(std::string availability)
                {
                    if(availability.compare(Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE) == 0)
                    {
                        return Search::Swallow::SearchConstants::MEETING_ROOM_ICON_AVAILABLE;
                    }
                    else if(availability.compare(Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE_SOON) == 0)
                    {
                        return Search::Swallow::SearchConstants::MEETING_ROOM_ICON_AVAILABLE_SOON;
                    }
                    else if(availability.compare(Search::Swallow::SearchConstants::MEETING_ROOM_OCCUPIED) == 0)
                    {
                        return Search::Swallow::SearchConstants::MEETING_ROOM_ICON_OCCUPIED;
                    }
                    return "";
                }
            }
            
            void SearchResultSectionController::AddSearchResultsToModel(const std::vector<Search::SdkModel::SearchResultModel>& unorderedResults)
            {
				for(int i = 0; i < m_lastAddedResults.size(); ++i)
				{
					const Search::SdkModel::SearchResultModel& model(m_lastAddedResults[i]);
					std::string subtitle = model.GetSubtitle();
					std::string category = model.GetCategory();
					if (model.GetCategory() == Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME)
					{
						// Availability is no longer a subtitle as that affects search results.
						Search::Swallow::SdkModel::SwallowMeetingRoomResultModel meetingRoomModel = Search::Swallow::SdkModel::SearchParser::TransformToSwallowMeetingRoomResult(model);
						subtitle = meetingRoomModel.GetOfficeLocation();

						category = GetMeetingRoomAvailablityIcon(meetingRoomModel.GetAvailability());
					}
					else if(model.GetCategory() == Search::Swallow::SearchConstants::WORKING_GROUP_CATEGORY_NAME)
					{
						Search::Swallow::SdkModel::SwallowWorkingGroupResultModel workingGroupmodel = Search::Swallow::SdkModel::SearchParser::TransformToSwallowWorkingGroupResult(model);
						subtitle = workingGroupmodel.GetOfficeLocation();
					}
					else if(model.GetCategory() == Search::Swallow::SearchConstants::TOILETS_CATEGORY_NAME || model.GetCategory() == Search::Swallow::SearchConstants::PRINT_STATION_CATEGORY_NAME)
					{
						Search::Swallow::SdkModel::SwallowFacilityResultModel facilityModel = Search::Swallow::SdkModel::SearchParser::TransformToSwallowFacilityResult(model);
						subtitle = facilityModel.GetOfficeLocation();
					}

					m_menuOptions.AddItem(model.GetIdentifier(),
										  model.GetTitle(),
										  subtitle,
										  category,
										  Eegeo_NEW(SearchResultItemModel)(model.GetIdentifier(),
																		   model.GetTitle(),
																		   model.GetLocation().ToECEF(),
																		   model.IsInterior(),
																		   model.GetBuildingId(),
																		   model.GetFloor(),
																		   m_searchMenuViewModel,
																		   m_searchResultPoiViewModel,
																		   GetOriginalIndexForSearchResult(unorderedResults, model),
																		   m_messageBus,
																		   m_menuReaction));
				}
            }

            void SearchResultSectionController::OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message)
            {
                for(int i = 0; i < m_lastAddedResults.size(); ++i)
                {
                    const Search::SdkModel::SearchResultModel& model(m_lastAddedResults[i]);
                    m_menuOptions.RemoveItem(model.GetIdentifier());
                }

                m_lastAddedResults = message.GetResults();
                const std::vector<Search::SdkModel::SearchResultModel>& unorderedResults = message.GetResults();

                OrderWrapper orderWrapper(m_order);
                std::stable_sort(m_lastAddedResults.begin(), m_lastAddedResults.end(), orderWrapper);

                AddSearchResultsToModel(unorderedResults);
            }

            void SearchResultSectionController::OnSearchQueryRemovedMessage(const Search::SearchQueryRemovedMessage& message)
            {
                for(int i = 0; i < m_lastAddedResults.size(); ++i)
                {
                    const Search::SdkModel::SearchResultModel& model(m_lastAddedResults[i]);
                    m_menuOptions.RemoveItem(model.GetIdentifier());
                }

                m_lastAddedResults.clear();
            }
            
            void SearchResultSectionController::OnAvailabilityChanged(const ExampleApp::SearchResultOnMap::SearchResultMeetingAvailabilityChanged& message)
            {
                const std::vector<Search::SdkModel::SearchResultModel>& unorderedResults = m_lastAddedResults;

                for(int i = 0; i < m_lastAddedResults.size(); ++i)
				{
                	const Search::SdkModel::SearchResultModel& model(m_lastAddedResults[i]);
                    if(model.GetIdentifier() == message.GetModel().GetIdentifier())
                    {
						int availability;
						if (message.GetAvailability() == "available")
						{
							availability = 1;
						}
						if (message.GetAvailability() == "available_soon")
						{
							availability = 2;
						}
						if (message.GetAvailability() == "occupied")
						{
							availability = 3;
						}
						unorderedResults[i].SetAvailability(availability);
						break;
                    }
				}

                for(int i = 0; i < m_lastAddedResults.size(); ++i)
                {
                    const Search::SdkModel::SearchResultModel& model(m_lastAddedResults[i]);
                    m_menuOptions.RemoveItem(model.GetIdentifier());
                }

                m_lastAddedResults = unorderedResults;
                OrderWrapper orderWrapper(m_order);
                std::stable_sort(m_lastAddedResults.begin(), m_lastAddedResults.end(), orderWrapper);

                AddSearchResultsToModel(unorderedResults);
            }


            SearchResultSectionController::SearchResultSectionController(Menu::View::IMenuViewModel& searchMenuViewModel,
                                                                         Menu::View::IMenuOptionsModel& menuOptions,
                                                                         ISearchResultSectionOrder& order,
                                                                         ExampleAppMessaging::TMessageBus& messageBus,
                                                                         const Menu::View::IMenuReactionModel& menuReaction,
                                                                         SearchResultPoi::View::ISearchResultPoiViewModel& searchResultPoiViewModel)
            : m_searchMenuViewModel(searchMenuViewModel)
            , m_menuOptions(menuOptions)
            , m_order(order)
            , m_messageBus(messageBus)
            , m_searchResultReceivedHandler(this, &SearchResultSectionController::OnSearchQueryResponseReceivedMessage)
            , m_searchQueryRemovedHandler(this, &SearchResultSectionController::OnSearchQueryRemovedMessage)
            , m_menuReaction(menuReaction)
            , m_searchResultPoiViewModel(searchResultPoiViewModel)
            , m_availabilityChangedHandlerBinding(this, &SearchResultSectionController::OnAvailabilityChanged)
            {
                m_messageBus.SubscribeUi(m_searchResultReceivedHandler);
                m_messageBus.SubscribeUi(m_searchQueryRemovedHandler);
                m_messageBus.SubscribeNative(m_availabilityChangedHandlerBinding);
            }

            SearchResultSectionController::~SearchResultSectionController()
            {
                m_messageBus.UnsubscribeUi(m_searchQueryRemovedHandler);
                m_messageBus.UnsubscribeUi(m_searchResultReceivedHandler);
                m_messageBus.UnsubscribeNative(m_availabilityChangedHandlerBinding);
            }
        }
    }
}
