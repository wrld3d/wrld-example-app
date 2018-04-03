// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <map>
#include "SearchQueryPerformer.h"
#include "ISearchService.h"
#include "ISearchResultRepository.h"
#include "IInterestPointProvider.h"
#include "LatLongAltitude.h"
#include "RenderCamera.h"
#include "SearchResultModel.h"
#include "BidirectionalBus.h"
#include "SearchQueryResultsRemovedMessage.h"
#include "CameraState.h"

namespace
{
    float GetSearchRadius(ExampleApp::AppCamera::SdkModel::IAppCameraController& cameraController)
    {
        const float SearchRadiusMin = 1000.f;
        const float SearchRadiusMax = 50000.f;
        Eegeo::Space::LatLongAltitude location = Eegeo::Space::LatLongAltitude::FromECEF(cameraController.GetCameraState().LocationEcef());
        float radius = (location.GetAltitude() * Eegeo::Math::Tan(cameraController.GetRenderCamera().GetFOV()));
        return Eegeo::Clamp(radius, SearchRadiusMin, SearchRadiusMax);
    }
}

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            SearchQueryPerformer::SearchQueryPerformer(ISearchService& searchService,
                                                       ISearchResultRepository& searchResultRepository,
                                                       ExampleApp::AppCamera::SdkModel::IAppCameraController& cameraController,
                                                       ExampleAppMessaging::TMessageBus& messageBus)
                : m_searchService(searchService)
                , m_searchResultsRepository(searchResultRepository)
                , m_pSearchResultResponseReceivedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<SearchQueryPerformer, const SearchQuery&, const std::vector<SearchResultModel>&>))(this, &SearchQueryPerformer::HandleSearchResultsResponseReceived))
                , m_previousQuery("", false, false, Eegeo::Space::LatLongAltitude(0.0, 0.0, 0.0), 0.f)
                , m_hasQuery(false)
                , m_cameraController(cameraController)
                , m_messageBus(messageBus)
            {
                m_searchService.InsertOnReceivedQueryResultsCallback(*m_pSearchResultResponseReceivedCallback);
            }

            SearchQueryPerformer::~SearchQueryPerformer()
            {
                m_searchService.RemoveOnReceivedQueryResultsCallback(*m_pSearchResultResponseReceivedCallback);
                
                Eegeo_DELETE m_pSearchResultResponseReceivedCallback;
            }

            bool SearchQueryPerformer::HasQuery() const
            {
                return m_hasQuery;
            }

            void SearchQueryPerformer::PerformSearchQuery(const std::string& query, bool isTag, bool tryInteriorSearch, const std::string& interiorId)
            {
                Eegeo::Space::LatLongAltitude location = Eegeo::Space::LatLongAltitude::FromECEF(m_cameraController.GetCameraState().InterestPointEcef());
                PerformSearchQuery(query, isTag, tryInteriorSearch, location, false, interiorId);
            }
            
            void SearchQueryPerformer::PerformSearchQuery(const std::string& query, bool isTag, bool tryInteriorSearch, float radius, const std::string& interiorId)
            {
                Eegeo::Space::LatLongAltitude location = Eegeo::Space::LatLongAltitude::FromECEF(m_cameraController.GetCameraState().InterestPointEcef());
                PerformSearchQuery(query, isTag, tryInteriorSearch, location, radius, interiorId);
            }

            void SearchQueryPerformer::PerformSearchQuery(const std::string& query,
                    bool isTag,
                    bool tryInteriorSearch,
                    const Eegeo::Space::LatLongAltitude& location,
                    bool startAtGPSLocation,
                    const std::string& interiorId)
            {
                const float radius = GetSearchRadius(m_cameraController);
                PerformSearchQuery(query, isTag, tryInteriorSearch, location, radius, startAtGPSLocation, interiorId);
            }
            
            void SearchQueryPerformer::PerformSearchQuery(const std::string& query,
                                                          bool isTag,
                                                          bool tryInteriorSearch,
                                                          const Eegeo::Space::LatLongAltitude& location,
                                                          float radius,
                                                          bool startAtGPSLocation,
                                                          const std::string& interiorId)
            {
                m_hasQuery = true;
                Eegeo::Space::LatLongAltitude searchLocation = location;
                if (startAtGPSLocation)
                {
                    searchLocation = Eegeo::Space::LatLongAltitude::FromECEF(m_cameraController.GetRenderCamera().GetEcefLocation());
                }
                SearchQuery searchQuery(query, isTag, tryInteriorSearch, searchLocation, radius, interiorId);
                
                m_previousQuery = searchQuery;
                m_searchService.PerformLocationQuerySearch(searchQuery);
            }

            void SearchQueryPerformer::RemoveSearchQueryResults()
            {
                m_hasQuery = false;

                m_searchService.CancelInFlightQueries();
                
                RemoveExistingSearchResults();

                m_queryResultsClearedCallbacks.ExecuteCallbacks();
                m_messageBus.Publish(SearchQueryResultsRemovedMessage());
            }

            void SearchQueryPerformer::InsertOnSearchResultsClearedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_queryResultsClearedCallbacks.AddCallback(callback);
            }

            void SearchQueryPerformer::RemoveOnSearchResultsClearedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_queryResultsClearedCallbacks.RemoveCallback(callback);
            }

            void SearchQueryPerformer::HandleSearchResultsResponseReceived(const SearchQuery& query,
                    const std::vector<SearchResultModel>& results)
            {
                // Ideally we should keep merge the new results into the old result set in a stable way, so that the
                // result list doesn't jumble up when we move about and perform new searches.

                std::map<SearchResultModel, size_t> currentRepoHash;
                std::set<size_t> retainedResultIndices;
                std::vector<SearchResultModel*> newResultTemporaryStorage;
                const int topIndexBeforeAddingNewResult = static_cast<int>(m_searchResultsRepository.GetItemCount() - 1);

                // First of all lets map the contents of the results repo so we can easily look results up later.
                // Map the result to its index.
                for(size_t i = 0; i < m_searchResultsRepository.GetItemCount(); ++ i)
                {
                    SearchResultModel* pItem = m_searchResultsRepository.GetItemAtIndex(i);
                    currentRepoHash.insert(std::make_pair(*pItem, i));
                }

                // For the new results, check if we already have the result using the map. If so, we flag the results
                // index as 'retained'. This will be used later when removing old results. If we have not seen the result
                // before, add it to a new temporary vector.
                for(std::vector<SearchResultModel>::const_iterator it = results.begin();
                        it != results.end();
                        ++ it)
                {
                    std::map<SearchResultModel, size_t>::iterator mapIt = currentRepoHash.find(*it);

                    if(mapIt == currentRepoHash.end())
                    {
                        SearchResultModel* pItem = Eegeo_NEW(SearchResultModel)(*it);

                        newResultTemporaryStorage.push_back(pItem);
                    }
                    else
                    {
                        retainedResultIndices.insert(mapIt->second);
                    }
                }

                // Walk backwards over the repository removing old results which are not retained, by inspection of
                // the retained indices.
                for(int i = topIndexBeforeAddingNewResult; i >= 0; --i)
                {
                    if(retainedResultIndices.find(i) == retainedResultIndices.end())
                    {
                        SearchResultModel* pItem = m_searchResultsRepository.GetItemAtIndex(i);
                        m_searchResultsRepository.RemoveItem(pItem);
                        Eegeo_DELETE pItem;
                    }
                }

                // Add the new results on the end after removing the old results.
                for(std::vector<SearchResultModel*>::const_iterator it = newResultTemporaryStorage.begin();
                        it != newResultTemporaryStorage.end();
                        ++ it)
                {
                    m_searchResultsRepository.AddItem(*it);
                }
            }

            void SearchQueryPerformer::RemoveExistingSearchResults()
            {
                while(m_searchResultsRepository.GetItemCount() > 0)
                {
                    SearchResultModel* pItem = m_searchResultsRepository.GetItemAtIndex(0);
                    m_searchResultsRepository.RemoveItem(pItem);
                    Eegeo_DELETE pItem;
                }
            }
        }
    }
}
