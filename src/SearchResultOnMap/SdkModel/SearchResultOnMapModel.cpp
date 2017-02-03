// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultOnMapItemModel.h"
#include "SearchResultOnMapModel.h"
#include "IWorldPinsService.h"
#include "ISearchResultOnMapFactory.h"
#include "ISearchResultRepository.h"
#include "SearchResultModel.h"
#include "ISearchResultIconKeyMapper.h"
#include "WorldPinFocusData.h"
#include "WorldPinInteriorData.h"
#include "ISearchResultMyPinsService.h"
#include "Logger.h"
#include "SwallowSearchParser.h"
#include "YelpSearchJsonParser.h"
#include "YelpSearchResultModel.h"
#include "SearchVendorNames.h"
#include "WorldPinItemModel.h"
#include "IMyPinsService.h"
#include "MyPinModel.h"
#include "YelpParsingHelpers.h"
#include "WorldPinVisibility.h"
#include "SwallowSearchConstants.h"
#include "ISearchService.h"
#include "SearchResultSectionItemSelectedMessage.h"
#include "YelpParsingHelpers.h"

#include <algorithm>

using ExampleApp::Search::SdkModel::SearchResultModel;

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace SdkModel
        {
            namespace
            {
                struct IsMatchingIdentifier
                {
                    IsMatchingIdentifier(const std::string& identifier)
                    : m_identifier(identifier)
                    {}
                    
                    bool operator()(const Search::SdkModel::SearchResultModel& searchResultModel) const
                    {
                        return m_identifier == searchResultModel.GetIdentifier();
                    }
                private:
                    const std::string m_identifier;
                };
                
                struct IsFocusable
                {
                    bool operator()(const Search::SdkModel::SearchResultModel& searchResultModel) const
                    {
                        return searchResultModel.GetPrimaryTag() != Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME;
                    }
                };
                
                std::string GetDepartmentFromSearchResultModel(const Search::SdkModel::SearchResultModel& searchResultModel)
                {
                    if (searchResultModel.GetPrimaryTag() == Search::Swallow::SearchConstants::DEPARTMENT_CATEGORY_NAME)
                    {
                        return searchResultModel.GetTitle();
                    }
                    else if (searchResultModel.GetPrimaryTag() == Search::Swallow::SearchConstants::PERSON_CATEGORY_NAME)
                    {
                        const Search::Swallow::SdkModel::SwallowPersonResultModel& person = Search::Swallow::SdkModel::SearchParser::TransformToSwallowPersonResult(searchResultModel);
                        return person.GetWorkingGroup();
                    }
                    return std::string();
                }
                
                struct VisibilityMaskGenerator
                {
                    typedef const Search::SdkModel::SearchResultModel argument_type;
                    
                    static inline VisibilityMaskGenerator Build(const Search::SdkModel::SearchResultModel* pCurrentSelection)
                    {
                        const bool isDepartment = (pCurrentSelection != NULL)
                            ? (pCurrentSelection->GetPrimaryTag() == Search::Swallow::SearchConstants::DEPARTMENT_CATEGORY_NAME)
                            : false;

                        const std::string& selectedDepartment = isDepartment
                            ? GetDepartmentFromSearchResultModel(*pCurrentSelection)
                            : std::string();
                        
                        return VisibilityMaskGenerator(isDepartment, selectedDepartment);
                    }
                    
                    int operator()(const Search::SdkModel::SearchResultModel& searchResultModel, const ExampleApp::WorldPins::SdkModel::WorldPinItemModel& worldPinItemModel) const
                    {
                        int visibilityMask = worldPinItemModel.VisibilityMask();
                        if (IsSearchVisible(searchResultModel))
                        {
                            visibilityMask |= WorldPins::SdkModel::WorldPinVisibility::Search;
                        }
                        else
                        {
                            visibilityMask &= ~WorldPins::SdkModel::WorldPinVisibility::Search;
                        }
                        
                        if (IsMeetingRoomVisible(searchResultModel))
                        {
                            visibilityMask |= WorldPins::SdkModel::WorldPinVisibility::MeetingRoom;
                        }
                        else
                        {
                            visibilityMask &= ~WorldPins::SdkModel::WorldPinVisibility::MeetingRoom;
                        }

                        return visibilityMask;
                    }
                    
                private:
                    VisibilityMaskGenerator(bool isDepartment,
                                            const std::string& tagId)
                    : m_isDepartment(isDepartment)
                    , m_tagId(tagId)
                    {
                        
                    }
                    
                    bool IsSearchVisible(const Search::SdkModel::SearchResultModel& searchResultModel) const
                    {
                        if (m_isDepartment)
                        {
                            const std::string& department = GetDepartmentFromSearchResultModel(searchResultModel);
                            return m_tagId == department;
                        }
                        else
                        {
                            return true;
                        }
                    }
                    
                    bool IsMeetingRoomVisible(const Search::SdkModel::SearchResultModel& searchResultModel) const
                    {
                        return searchResultModel.GetPrimaryTag() == Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME;
                    }
                    
                    const bool m_isDepartment;
                    const std::string m_tagId;
                };
            }

            SearchResultOnMapModel::SearchResultOnMapModel(WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                           MyPins::SdkModel::IMyPinsService& myPinsService,
                                                           View::ISearchResultOnMapFactory& searchResultOnMapFactory,
                                                           Search::SdkModel::MyPins::ISearchResultMyPinsService& searchResultOnMapMyPinsService,
                                                           TagSearch::ISearchResultIconKeyMapper& searchResultIconKeyMapper,
                                                           ExampleAppMessaging::TMessageBus& messageBus,
                                                           Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                                           Search::SdkModel::ISearchService& searchService)
            : m_searchResultRepository(searchResultRepository)
            , m_searchService(searchService)
            , m_searchResultIconKeyMapper(searchResultIconKeyMapper)
            , m_searchResultOnMapMyPinsService(searchResultOnMapMyPinsService)
            , m_searchResultOnMapFactory(searchResultOnMapFactory)
            , m_myPinsService(myPinsService)
            , m_messageBus(messageBus)
            , m_worldPinsService(worldPinsService)
            , m_searchResultAddedCallback(this, &SearchResultOnMapModel::HandleAddedSearchResult)
            , m_searchResultRemovedCallback(this, &SearchResultOnMapModel::HandleRemovedSearchResult)
            , m_searchResultsCallback(this, &SearchResultOnMapModel::HandleSearchResultsReceived)
            , m_searchResultPinnedCallback(this, &SearchResultOnMapModel::HandleSearchResultPinned)
            , m_searchResultUnpinnedCallback(this, &SearchResultOnMapModel::HandleSearchResultUnpinned)
            , m_availbilityChangedMessage(this, &SearchResultOnMapModel::OnSearchResultMeetingAvailbilityChanged)
            , m_searchResultSectionItemSelectedMessageHandler(this, &SearchResultOnMapModel::OnSearchResultSectionItemSelected)
            {
                m_searchResultRepository.InsertItemAddedCallback(m_searchResultAddedCallback);
                m_searchResultRepository.InsertItemRemovedCallback(m_searchResultRemovedCallback);
                m_searchService.InsertOnReceivedQueryResultsCallback(m_searchResultsCallback);
                
                m_searchResultOnMapMyPinsService.InsertSearchResultPinnedCallback(m_searchResultPinnedCallback);
                m_searchResultOnMapMyPinsService.InsertSearchResultUnpinnedCallback(m_searchResultUnpinnedCallback);

                for(size_t i = 0; i < m_searchResultRepository.GetItemCount(); ++ i)
                {
                    Search::SdkModel::SearchResultModel* pModel = m_searchResultRepository.GetItemAtIndex(i);
                    HandleAddedSearchResult(pModel);
                }
                
                m_messageBus.SubscribeNative(m_availbilityChangedMessage);
                m_messageBus.SubscribeNative(m_searchResultSectionItemSelectedMessageHandler);
            }

            SearchResultOnMapModel::~SearchResultOnMapModel()
            {
                m_messageBus.UnsubscribeNative(m_availbilityChangedMessage);
                m_messageBus.UnsubscribeNative(m_searchResultSectionItemSelectedMessageHandler);
                
                m_searchService.RemoveOnReceivedQueryResultsCallback(m_searchResultsCallback);
                m_searchResultRepository.RemoveItemAddedCallback(m_searchResultAddedCallback);
                m_searchResultRepository.RemoveItemRemovedCallback(m_searchResultRemovedCallback);
                
                m_searchResultOnMapMyPinsService.RemoveSearchResultPinnedCallback(m_searchResultPinnedCallback);
                m_searchResultOnMapMyPinsService.RemoveSearchResultUnpinnedCallback(m_searchResultUnpinnedCallback);

                while(m_searchResultsToPinModel.size())
                {
                    mapIt it = m_searchResultsToPinModel.begin();
                    Search::SdkModel::SearchResultModel searchResultModel = it->first;
                    Search::SdkModel::SearchResultModel* pSearchResultModel = &searchResultModel;
                    HandleRemovedSearchResult(pSearchResultModel);
                }
            }

            void SearchResultOnMapModel::HandleAddedSearchResult(SearchResultModel*& pSearchResultModel)
            {
                m_activeSearchResults.insert(*pSearchResultModel);
                
                if(m_searchResultOnMapMyPinsService.IsSearchResultPinned(*pSearchResultModel))
                {
                    m_hiddenSearchResultsDueToMyPins.insert(*pSearchResultModel);
                    
                    // Add Search to visibility mask
                    MyPins::SdkModel::MyPinModel myPinModel;
                    bool success = m_searchResultOnMapMyPinsService.TryGetPinForSearchResult(*pSearchResultModel, myPinModel);
                    Eegeo_ASSERT(success, "MyPinModel for SearchResultModel not in SearchResultOnMapMyPinsService when it was reported as pinned");
                    
                    WorldPins::SdkModel::WorldPinItemModel* pWorldPinItemModel = NULL;
                    if(m_myPinsService.TryGetWorldPinItemModelForMyPin(myPinModel.Identifier(), pWorldPinItemModel))
                    {
                        int newVisibilityMask = pWorldPinItemModel->VisibilityMask() | WorldPins::SdkModel::WorldPinVisibility::Search;
                        pWorldPinItemModel->SetVisibilityMask(newVisibilityMask);
                    }
                    
                }
                else if((pSearchResultModel->GetPrimaryTag() != Search::Swallow::SearchConstants::OFFICE_CATEGORY_NAME)
                        && (pSearchResultModel->GetPrimaryTag() != Search::Swallow::SearchConstants::TRANSITION_CATEGORY_NAME))
                {
                    AddSearchResultOnMap(*pSearchResultModel);
                }
            }

            void SearchResultOnMapModel::HandleRemovedSearchResult(SearchResultModel*& pSearchResultModel)
            {
                m_activeSearchResults.erase(*pSearchResultModel);
                
                if(m_searchResultOnMapMyPinsService.IsSearchResultPinned(*pSearchResultModel))
                {
                    // If it is pinned, we should not have a search result on map.
                    Eegeo_ASSERT(m_searchResultsToPinModel.find(*pSearchResultModel) == m_searchResultsToPinModel.end());
                    
                    // Result should be hidden due to user pinning, remove from the hidden set.
                    setIt hiddenItemIterator(m_hiddenSearchResultsDueToMyPins.find(*pSearchResultModel));
                    Eegeo_ASSERT(hiddenItemIterator != m_hiddenSearchResultsDueToMyPins.end());
                    m_hiddenSearchResultsDueToMyPins.erase(hiddenItemIterator);
                    
                    // Remove Search from visibility mask
                    MyPins::SdkModel::MyPinModel myPinModel;
                    bool success = m_searchResultOnMapMyPinsService.TryGetPinForSearchResult(*pSearchResultModel, myPinModel);
                    Eegeo_ASSERT(success, "MyPinModel for SearchResultModel not in SearchResultOnMapMyPinsService when it was reported as pinned");
                    
                    WorldPins::SdkModel::WorldPinItemModel* pWorldPinItemModel = NULL;
                    if(m_myPinsService.TryGetWorldPinItemModelForMyPin(myPinModel.Identifier(), pWorldPinItemModel))
                    {
                        int newVisibilityMask = pWorldPinItemModel->VisibilityMask() & ~WorldPins::SdkModel::WorldPinVisibility::Search;
                        pWorldPinItemModel->SetVisibilityMask(newVisibilityMask);
                    }
                }
                else if((pSearchResultModel->GetPrimaryTag() != Search::Swallow::SearchConstants::OFFICE_CATEGORY_NAME)
                        && (pSearchResultModel->GetPrimaryTag() != Search::Swallow::SearchConstants::TRANSITION_CATEGORY_NAME))
                {
                    RemoveSearchResultOnMap(*pSearchResultModel);
                }
            }
            
            void SearchResultOnMapModel::HandleSearchResultsReceived(const Search::SdkModel::SearchQuery &query,
                                                                     const std::vector<Search::SdkModel::SearchResultModel> &results)
            {
                for(std::vector<Search::SdkModel::SearchResultModel>::const_iterator it = results.begin(); it != results.end(); it++)
                {
                    const Search::SdkModel::SearchResultModel& result = (*it);
                    if(result.GetPrimaryTag() == Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME)
                    {
                        mapIt pinIt = m_searchResultsToPinModel.find(result);
                        if(pinIt == m_searchResultsToPinModel.end())
                        {
                            continue;
                        }
                        
                        std::string availabilityIconKey = m_searchResultIconKeyMapper.GetIconKeyFromSearchResult(result);
                        
                        ExampleApp::WorldPins::SdkModel::WorldPinItemModel* pPinItemModel = pinIt->second;
                        m_worldPinsService.UpdatePinCategory(*pPinItemModel, availabilityIconKey);
                    }
                }
                
                RefreshPinsForSelection();
            }
            
            void SearchResultOnMapModel::OnSearchResultSectionItemSelected(const SearchResultSection::SearchResultSectionItemSelectedMessage& message)
            {
                m_currentSelectedId = message.Identifier();
                RefreshPinsForSelection();
            }
            
            const Search::SdkModel::SearchResultModel* SearchResultOnMapModel::GetSelectedSearchResultModelOrNull() const
            {
                const Search::SdkModel::SearchResultModel* pCurrentSelection = NULL;
                if (!m_currentSelectedId.empty())
                {
                    std::set<Search::SdkModel::SearchResultModel>::iterator iter = std::find_if(m_activeSearchResults.begin(), m_activeSearchResults.end(), IsMatchingIdentifier(m_currentSelectedId));
                
                
                    if (iter != m_activeSearchResults.end())
                    {
                        const Search::SdkModel::SearchResultModel& result = *iter;
                        pCurrentSelection = &result;
                    }
                }
                
                return pCurrentSelection;
            }
            
            void SearchResultOnMapModel::RefreshPinsForSelection()
            {
                typedef std::map<Search::SdkModel::SearchResultModel, ExampleApp::WorldPins::SdkModel::WorldPinItemModel*> SearchResultToPin;
                
                const Search::SdkModel::SearchResultModel* pCurrentSelection = GetSelectedSearchResultModelOrNull();
                const VisibilityMaskGenerator& visibilityMaskGenerator = VisibilityMaskGenerator::Build(pCurrentSelection);
                
                IsFocusable focusablePredicate;
                
                for (SearchResultToPin::iterator iter = m_searchResultsToPinModel.begin(); iter != m_searchResultsToPinModel.end(); ++iter)
                {
                    const Search::SdkModel::SearchResultModel& searchResultModel = iter->first;
                    ExampleApp::WorldPins::SdkModel::WorldPinItemModel* pWorldPinItemModel = iter->second;

                    const int visibilityMask = visibilityMaskGenerator(searchResultModel, *pWorldPinItemModel);

                    pWorldPinItemModel->SetVisibilityMask(visibilityMask);
                    
                    const bool isFocusable = focusablePredicate(searchResultModel);
                    
                    pWorldPinItemModel->SetFocusable(isFocusable);
               }
            }
            
            
            void SearchResultOnMapModel::HandleSearchResultPinned(SearchResultModel& searchResultModel)
            {
                // Search result is now pinned, so will be responsibility of MyPin system to visualise.
                // Need to hide the search result on map visualisation.
                
                // It seems reasonable to expect that the pinned search result is an active search result
                // represented on the map (else, how did we pin it), but this is not neccessarily the case.
                // We might do a search, pin it, cancel the search, open the pinned item details then unpin
                // *and* pin again. Consequently the following test is an if rather than an assert.
                
                setIt it = m_activeSearchResults.find(searchResultModel);
                
                if(it != m_activeSearchResults.end())
                {
                    // It is an active search result, so add it to the hidden set, and remove the
                    // corresponding search result on map.
                    
                    m_hiddenSearchResultsDueToMyPins.insert(searchResultModel);
                    RemoveSearchResultOnMap(searchResultModel);
                }
            }
            
            void SearchResultOnMapModel::HandleSearchResultUnpinned(SearchResultModel& searchResultModel)
            {
                // The result is now unpinned -- if we have an active search result for this pinned result,
                // it will be hidden. We should unhide it.
                
                setIt hiddenItemIterator(m_hiddenSearchResultsDueToMyPins.find(searchResultModel));
                if(hiddenItemIterator != m_hiddenSearchResultsDueToMyPins.end())
                {
                    AddSearchResultOnMap(searchResultModel);
                    m_hiddenSearchResultsDueToMyPins.erase(hiddenItemIterator);
                }
            }
            
            void SearchResultOnMapModel::OnSearchResultMeetingAvailbilityChanged(const SearchResultMeetingAvailabilityChanged& meetingAvailbilityChangedMessage)
            {
                const SearchResultModel& model = meetingAvailbilityChangedMessage.GetModel();
                mapIt it = m_searchResultsToPinModel.find(model);
                
                if (it != m_searchResultsToPinModel.end())
                {
                    const WorldPins::SdkModel::WorldPinItemModel& worldPinModel = *(it->second);
                    const SearchResultModel& mutatedModel = Search::Swallow::SdkModel::SearchParser::MutateMeetingRoomAvailability(model, meetingAvailbilityChangedMessage.GetAvailability());
                    m_worldPinsService.UpdatePinCategory(worldPinModel, m_searchResultIconKeyMapper.GetIconKeyFromSearchResult(mutatedModel));
                }
            }
            
            void SearchResultOnMapModel::AddSearchResultOnMap(SearchResultModel& searchResultModel)
            {
                mapIt it = m_searchResultsToPinModel.find(searchResultModel);
                
                Eegeo_ASSERT(it == m_searchResultsToPinModel.end(),
                             "Trying to add a world pin for a search result, but pin has already been added.");
                
                View::SearchResultOnMapItemModel* pSearchResultOnMapItemModel = m_searchResultOnMapFactory.CreateSearchResultOnMapItemModel(searchResultModel);
                
                const std::string& pinIconKey = m_searchResultIconKeyMapper.GetIconKeyFromSearchResult(searchResultModel);
                
                std::string ratingsImage = "";
                int reviewCount = 0;
                
                Search::Yelp::SdkModel::Helpers::TryParseReviewDetails(searchResultModel, ratingsImage, reviewCount);
                
                WorldPins::SdkModel::WorldPinFocusData worldPinFocusData(searchResultModel.GetTitle(),
                                                                         searchResultModel.GetSubtitle(),
                                                                         searchResultModel.GetVendor(),
                                                                         searchResultModel.GetJsonData(),
                                                                         ratingsImage,
                                                                         reviewCount);
                
                WorldPins::SdkModel::WorldPinInteriorData worldPinInteriorData(searchResultModel.GetBuildingId(), searchResultModel.GetFloor());
                
                ExampleApp::WorldPins::SdkModel::WorldPinItemModel *pinItemModel = m_worldPinsService.AddPin(pSearchResultOnMapItemModel,
                                                                                                             NULL,
                                                                                                             worldPinFocusData,
                                                                                                             searchResultModel.IsInterior(),
                                                                                                             worldPinInteriorData,
                                                                                                             searchResultModel.GetLocation(),
                                                                                                             pinIconKey,
                                                                                                             searchResultModel.GetHeightAboveTerrainMetres(),
                                                                                                             WorldPins::SdkModel::WorldPinVisibility::Search,
                                                                                                             searchResultModel.GetPrimaryTag(),
                                                                                                             searchResultModel.GetIdentifier());
                
                m_searchResultsToPinModel.insert(std::make_pair(searchResultModel, pinItemModel));
                
                RefreshPinsForSelection();
            }
            
            void SearchResultOnMapModel::RemoveSearchResultOnMap(SearchResultModel& searchResultModel)
            {
                mapIt it = m_searchResultsToPinModel.find(searchResultModel);
                Eegeo_ASSERT(it != m_searchResultsToPinModel.end(),
                             "Trying to remove the world pin for a search result, but no pin exists for result.");
                
                ExampleApp::WorldPins::SdkModel::WorldPinItemModel* pinItemModel = it->second;
                m_worldPinsService.RemovePin(pinItemModel);
                m_searchResultsToPinModel.erase(it);
                m_currentSelectedId.clear();
                RefreshPinsForSelection();
            }

        }
    }
}
