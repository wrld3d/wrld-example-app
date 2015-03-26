// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchRefreshService.h"
#include "ISearchService.h"
#include "ISearchQueryPerformer.h"
#include "LatLongAltitude.h"
#include "ICameraTransitionController.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            SearchRefreshService::SearchRefreshService(ISearchService& searchService,
                    ISearchQueryPerformer& searchQueryPerformer,
                    CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionsController,
                    float minimumSecondsBetweenUpdates,
                    float minimumMetresBetweenUpdates)
                : m_minimumSecondsBetweenUpdates(minimumSecondsBetweenUpdates)
                , m_minimumMetresSquaredBetweenUpdates(minimumMetresBetweenUpdates * minimumMetresBetweenUpdates)
                , m_searchService(searchService)
                , m_searchQueryPerformer(searchQueryPerformer)
                , m_cameraTransitionsController(cameraTransitionsController)
                , m_pSearchResultQueryIssuedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback1<SearchRefreshService, const SearchQuery&>))(this, &SearchRefreshService::HandleSearchQueryIssued))
                , m_pSearchResultResponseReceivedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<SearchRefreshService, const SearchQuery&, const std::vector<SearchResultModel>& >))(this, &SearchRefreshService::HandleSearchResultsResponseReceived))
                , m_pSearchQueryResultsClearedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<SearchRefreshService>)(this, &SearchRefreshService::HandleSearchQueryResultsCleared))
                , m_queriesPending(0)
                , m_searchResultsExist(false)
                , m_secondsSincePreviousRefresh(0.f)
                , m_cameraTransitioning(false)
                , m_enabled(true)
            {
                m_searchService.InsertOnPerformedQueryCallback(*m_pSearchResultQueryIssuedCallback);
                m_searchService.InsertOnReceivedQueryResultsCallback(*m_pSearchResultResponseReceivedCallback);
                m_searchQueryPerformer.InsertOnSearchResultsClearedCallback(*m_pSearchQueryResultsClearedCallback);
            }

            SearchRefreshService::~SearchRefreshService()
            {
                m_searchQueryPerformer.RemoveOnSearchResultsClearedCallback(*m_pSearchQueryResultsClearedCallback);
                m_searchService.RemoveOnReceivedQueryResultsCallback(*m_pSearchResultResponseReceivedCallback);
                m_searchService.RemoveOnPerformedQueryCallback(*m_pSearchResultQueryIssuedCallback);

                Eegeo_DELETE m_pSearchResultResponseReceivedCallback;
                Eegeo_DELETE m_pSearchResultQueryIssuedCallback;
                Eegeo_DELETE m_pSearchQueryResultsClearedCallback;
            }

            void SearchRefreshService::SetEnabled(bool enabled)
            {
                m_enabled = enabled;
            }

            void SearchRefreshService::TryRefreshSearch(float deltaSeconds, const Eegeo::dv3& ecefLocation)
            {
                if (!m_enabled)
                {
                    return;
                }
                if(m_searchResultsExist)
                {
                    m_secondsSincePreviousRefresh += deltaSeconds;
                }
                else
                {
                    m_secondsSincePreviousRefresh = 0.f;
                }

                if(m_queriesPending == 0 && m_searchResultsExist)
                {
                    if(m_cameraTransitionsController.IsTransitioning())
                    {
                        m_cameraTransitioning = true;
                        return;
                    }
                    else if(m_cameraTransitioning)
                    {
                        m_previousQueryLocationEcef = Eegeo::Space::LatLong::FromECEF(ecefLocation).ToECEF();
                        m_cameraTransitioning = false;
                    }

                    if(m_secondsSincePreviousRefresh >= m_minimumSecondsBetweenUpdates)
                    {
                        Eegeo::Space::LatLongAltitude currentLocation = Eegeo::Space::LatLongAltitude::FromECEF(ecefLocation);

                        double distanceMetresSq = (ecefLocation - m_previousQueryLocationEcef).LengthSq();

                        if(distanceMetresSq >= m_minimumMetresSquaredBetweenUpdates)
                        {
                            m_previousQueryLocationEcef = ecefLocation;
                            const SearchQuery& previousQuery = m_searchQueryPerformer.GetPreviousSearchQuery();
                            m_searchQueryPerformer.PerformSearchQuery(previousQuery.Query(), previousQuery.IsCategory(), currentLocation);

                            m_secondsSincePreviousRefresh = 0.f;
                        }
                    }
                }
            }

            void SearchRefreshService::HandleSearchQueryIssued(const SearchQuery& query)
            {
                ++ m_queriesPending;
            }

            void SearchRefreshService::HandleSearchResultsResponseReceived(const SearchQuery& query,
                    const std::vector<SearchResultModel>& results)
            {
                m_searchResultsExist = true;
                m_previousQueryLocationEcef = query.Location().ToECEF();
                -- m_queriesPending;
                Eegeo_ASSERT(m_queriesPending >= 0);
            }

            void SearchRefreshService::HandleSearchQueryResultsCleared()
            {
                m_searchResultsExist = false;
            }
        }
    }
}

