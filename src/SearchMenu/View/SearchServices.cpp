// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "SearchServices.h"
#include "SwallowSearchConstants.h"
#include "SwallowSearchParser.h"
#include "SearchQuery.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
		namespace View
		{
			SearchServices::SearchServices(ISearchProvider& searchProvider,
										   ExampleAppMessaging::TMessageBus& messageBus)
			: m_searchProvider(searchProvider)
			, m_messageBus(messageBus)
			, m_onSearchCallback(this, &SearchServices::OnSearch)
			, m_onSearchWithContextCallback(this, &SearchServices::OnSearchWithContext)
			, m_onCancelCallback(this, &SearchServices::OnCancel)
			, m_responseReceivedHandler(this, &SearchServices::OnSearchQueryResponseReceivedMessage)
			{
				m_searchProvider.InsertSearchPerformedCallback(m_onSearchCallback);
				m_searchProvider.InsertSearchWithContextCallback(m_onSearchWithContextCallback);
				m_searchProvider.InsertSearchCancelledCallback(m_onCancelCallback);

                m_messageBus.SubscribeUi(m_responseReceivedHandler);
            }

			SearchServices::~SearchServices()
			{
                m_messageBus.UnsubscribeUi(m_responseReceivedHandler);

				m_searchProvider.RemoveSearchCancelledCallback(m_onCancelCallback);
				m_searchProvider.RemoveSearchWithContextCallback(m_onSearchWithContextCallback);
				m_searchProvider.RemoveSearchPerformedCallback(m_onSearchCallback);
			}

			int SearchServices::GetResultOriginalIndexFromCurrentIndex(int index) const
			{
				return m_searchResults[index].GetOriginalIndex();
			}

			const SearchMenu::View::SearchServicesResult::TSdkSearchResult& SearchServices::GetSdkSearchResultByIndex(int index) const
			{
				return m_searchResults[index].GetSdkSearchResult();
			}

            void SearchServices::OnSearch(const std::string& searchQuery)
            {
				m_messageBus.Publish(SearchMenuPerformedSearchMessage(searchQuery, false, false));
            }

			void SearchServices::OnSearchWithContext(const std::string& searchQuery, const QueryContext& context)
			{
				m_messageBus.Publish(SearchMenuRefreshedSearchMessage(searchQuery,
																	  context.IsTag(),
																	  context.ShouldTryInterior(),
																	  context.ShouldZoomToBuildingsView(),
																	  context.Location(),
																	  context.Radius()));
			}

			void SearchServices::OnCancel()
			{
				// TO DO - cancel ongoing search
			}

			void SearchServices::OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message)
            {
				const std::vector<TSdkSearchResult>& sdkResults = message.GetResults();

				m_searchResults.clear();
				m_searchResults.reserve(CountResultsShown(sdkResults));

				for (std::vector<TSdkSearchResult>::const_iterator it = sdkResults.begin(); it != sdkResults.end(); it++)
				{
					if (!Search::Swallow::SearchConstants::ShouldShowTagAsSearchResult(it->GetPrimaryTag()))
						continue;

					std::string name = it->GetTitle();
					std::string desc = it->GetSubtitle();
					std::string icon = it->GetIconKey();

					HandleSpecialCases(*it, desc, icon);

					m_searchResults.push_back(SearchServicesResult(name, desc, icon,
																   static_cast<int>(std::distance(sdkResults.begin(), it)),
																   *it));
				}

				m_searchProvider.OnSearchResponseReceived(m_searchResults);
			}

			int SearchServices::CountResultsShown(const std::vector<TSdkSearchResult>& sdkResults)
			{
				int resultsShown = 0;

				for (std::vector<TSdkSearchResult>::const_iterator it = sdkResults.begin(); it != sdkResults.end(); it++)
				{
					if (Search::Swallow::SearchConstants::ShouldShowTagAsSearchResult(it->GetPrimaryTag()))
					{
						resultsShown++;
					}
				}

				return resultsShown;
			}

			void SearchServices::HandleSpecialCases(const TSdkSearchResult& sdkResult,
													std::string& description, std::string& iconName)
			{
				namespace SearchConstants = Search::Swallow::SearchConstants;
				namespace SwallowSdkModel = Search::Swallow::SdkModel;
				namespace SearchParser    = Search::Swallow::SdkModel::SearchParser;

				typedef SwallowSdkModel::SwallowMeetingRoomResultModel SwallowMeetingRoomResultModel;

				std::string tag = sdkResult.GetPrimaryTag();

				if (tag == SearchConstants::MEETING_ROOM_CATEGORY_NAME)
				{
					SwallowMeetingRoomResultModel newModel
							= SearchParser::TransformToSwallowMeetingRoomResult(sdkResult);

					description = newModel.GetOfficeLocation();
					iconName    = GetMeetingRoomAvailablityIcon(newModel.GetAvailability());
				}

				else if (tag == SearchConstants::TRAINING_ROOM_CATEGORY_NAME)
					description = SearchParser::TransformToSwallowTrainingRoomResult(sdkResult)
								  .GetOfficeLocation();

				else if (tag == SearchConstants::WORKING_GROUP_CATEGORY_NAME)
					description = SearchParser::TransformToSwallowWorkingGroupResult(sdkResult)
								  .GetOfficeLocation();

				else if (tag == SearchConstants::FACILITY_CATEGORY_NAME)
					description = SearchParser::TransformToSwallowFacilityResult(sdkResult)
								  .GetOfficeLocation();
			}

			std::string SearchServices::GetMeetingRoomAvailablityIcon(std::string availability)
			{
				namespace SearchConstants = Search::Swallow::SearchConstants;

				if (availability == SearchConstants::MEETING_ROOM_AVAILABLE)
					return SearchConstants::MEETING_ROOM_ICON_AVAILABLE;

				if (availability == SearchConstants::MEETING_ROOM_AVAILABLE_SOON)
					return SearchConstants::MEETING_ROOM_ICON_AVAILABLE_SOON;

				if (availability == SearchConstants::MEETING_ROOM_OCCUPIED)
					return SearchConstants::MEETING_ROOM_ICON_OCCUPIED;

				if (availability == SearchConstants::MEETING_ROOM_INACTIVE)
					return SearchConstants::MEETING_ROOM_ICON_INACTIVE;

				return "";
			}
		}
	}
}
