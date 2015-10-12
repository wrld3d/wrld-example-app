// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultOnMapItemModel.h"
#include "SearchResultOnMapModel.h"
#include "IWorldPinsService.h"
#include "ISearchResultOnMapFactory.h"
#include "ISearchResultRepository.h"
#include "SearchResultModel.h"
#include "ISearchResultIconCategoryMapper.h"
#include "WorldPinFocusData.h"
#include "WorldPinInteriorData.h"
#include "ISearchResultMyPinsService.h"
#include "Logger.h"
#include "YelpSearchJsonParser.h"
#include "YelpSearchResultModel.h"
#include "WorldPinItemModel.h"
#include "IMyPinsService.h"
#include "MyPinModel.h"
#include "WorldPinVisibility.h"

using ExampleApp::Search::SdkModel::SearchResultModel;

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace SdkModel
        {
            SearchResultOnMapModel::SearchResultOnMapModel(WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                           MyPins::SdkModel::IMyPinsService& myPinsService,
                                                           View::ISearchResultOnMapFactory& searchResultOnMapFactory,
                                                           Search::SdkModel::MyPins::ISearchResultMyPinsService& searchResultOnMapMyPinsService,
                                                           CategorySearch::ISearchResultIconCategoryMapper& searchResultIconCategoryMapper,
                                                           Search::SdkModel::ISearchResultRepository& searchResultRepository)
            : m_searchResultRepository(searchResultRepository)
            , m_searchResultIconCategoryMapper(searchResultIconCategoryMapper)
            , m_searchResultOnMapMyPinsService(searchResultOnMapMyPinsService)
            , m_searchResultOnMapFactory(searchResultOnMapFactory)
            , m_myPinsService(myPinsService)
            , m_worldPinsService(worldPinsService)
            , m_searchResultAddedCallback(this, &SearchResultOnMapModel::HandleAddedSearchResult)
            , m_searchResultRemovedCallback(this, &SearchResultOnMapModel::HandleRemovedSearchResult)
            , m_searchResultPinnedCallback(this, &SearchResultOnMapModel::HandleSearchResultPinned)
            , m_searchResultUnpinnedCallback(this, &SearchResultOnMapModel::HandleSearchResultUnpinned)
            {
                m_searchResultRepository.InsertItemAddedCallback(m_searchResultAddedCallback);
                m_searchResultRepository.InsertItemRemovedCallback(m_searchResultRemovedCallback);
                
                m_searchResultOnMapMyPinsService.InsertSearchResultPinnedCallback(m_searchResultPinnedCallback);
                m_searchResultOnMapMyPinsService.InsertSearchResultUnpinnedCallback(m_searchResultUnpinnedCallback);

                for(size_t i = 0; i < m_searchResultRepository.GetItemCount(); ++ i)
                {
                    Search::SdkModel::SearchResultModel* pModel = m_searchResultRepository.GetItemAtIndex(i);
                    HandleAddedSearchResult(pModel);
                }
            }

            SearchResultOnMapModel::~SearchResultOnMapModel()
            {
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
                else
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
                else
                {
                    RemoveSearchResultOnMap(*pSearchResultModel);
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
            
            void SearchResultOnMapModel::AddSearchResultOnMap(SearchResultModel& searchResultModel)
            {
                mapIt it = m_searchResultsToPinModel.find(searchResultModel);
                
                Eegeo_ASSERT(it == m_searchResultsToPinModel.end(),
                             "Trying to add a world pin for a search result, but pin has already been added.");
                
                View::SearchResultOnMapItemModel* pSearchResultOnMapItemModel = m_searchResultOnMapFactory.CreateSearchResultOnMapItemModel(searchResultModel);
                
                const int pinIconIndex = m_searchResultIconCategoryMapper.GetIconIndexFromSearchResult(searchResultModel);
                
                std::string ratingsImage = "";
                int reviewCount = 0;
                
                Search::Yelp::SdkModel::TryParseReviewDetails(searchResultModel, ratingsImage, reviewCount);
                
                WorldPins::SdkModel::WorldPinFocusData worldPinFocusData(searchResultModel.GetTitle(),
                                                                         searchResultModel.GetSubtitle(),
                                                                         ratingsImage,
                                                                         reviewCount);
                
                WorldPins::SdkModel::WorldPinInteriorData worldPinInteriorData(searchResultModel.GetBuildingId(), searchResultModel.GetFloor());
                
                ExampleApp::WorldPins::SdkModel::WorldPinItemModel *pinItemModel = m_worldPinsService.AddPin(pSearchResultOnMapItemModel,
                                                                                                             NULL,
                                                                                                             worldPinFocusData,
                                                                                                             searchResultModel.IsInterior(),
                                                                                                             worldPinInteriorData,
                                                                                                             searchResultModel.GetLocation(),
                                                                                                             pinIconIndex,
                                                                                                             searchResultModel.GetHeightAboveTerrainMetres(),
                                                                                                             WorldPins::SdkModel::WorldPinVisibility::Search);
                
                m_searchResultsToPinModel.insert(std::make_pair(searchResultModel, pinItemModel));
            }
            
            void SearchResultOnMapModel::RemoveSearchResultOnMap(SearchResultModel& searchResultModel)
            {
                mapIt it = m_searchResultsToPinModel.find(searchResultModel);
                Eegeo_ASSERT(it != m_searchResultsToPinModel.end(),
                             "Trying to remove the world pin for a search result, but no pin exists for result.");
                
                ExampleApp::WorldPins::SdkModel::WorldPinItemModel* pinItemModel = it->second;
                m_worldPinsService.RemovePin(pinItemModel);
                m_searchResultsToPinModel.erase(it);
            }

            SearchResultOnMapModel::mapIt SearchResultOnMapModel::begin()
            {
                return m_searchResultsToPinModel.begin();
            }

            SearchResultOnMapModel::mapIt SearchResultOnMapModel::end()
            {
                return m_searchResultsToPinModel.end();
            }
        }
    }
}
