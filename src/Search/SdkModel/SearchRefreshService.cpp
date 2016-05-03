// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchRefreshService.h"
#include "ISearchService.h"
#include "ISearchQueryPerformer.h"
#include "LatLongAltitude.h"
#include "ICameraTransitionController.h"

#include <algorithm>

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
                    float minimumInterestLateralDeltaAt1km,
                    float maximumInterestLateralSpeedAt1km)
                : m_minimumSecondsBetweenUpdates(minimumSecondsBetweenUpdates)
                , m_minimumInterestLateralDeltaAt1km(minimumInterestLateralDeltaAt1km)
                , m_maximumInterestLateralSpeedAt1km(maximumInterestLateralSpeedAt1km)
                , m_searchService(searchService)
                , m_searchQueryPerformer(searchQueryPerformer)
                , m_cameraTransitionsController(cameraTransitionsController)
                , m_pSearchResultQueryIssuedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback1<SearchRefreshService, const SearchQuery&>))(this, &SearchRefreshService::HandleSearchQueryIssued))
                , m_pSearchResultResponseReceivedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<SearchRefreshService, const SearchQuery&, const std::vector<SearchResultModel>& >))(this, &SearchRefreshService::HandleSearchResultsResponseReceived))
                , m_pSearchQueryResultsClearedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<SearchRefreshService>)(this, &SearchRefreshService::HandleSearchQueryResultsCleared))
                , m_queriesPending(0)
                , m_searchResultsExist(false)
                , m_secondsSincePreviousRefresh(0.f)
                , m_enabled(true)
                , m_previousQueryLocationEcef(Eegeo::dv3::Zero())
                , m_previousInterestEcefLocation(Eegeo::dv3::Zero())
                , m_previousQueryInterestDistance(0.f)
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
            
            bool SearchRefreshService::ShouldRefreshSearch(float deltaSeconds, const Eegeo::dv3& interestPointEcef, const Eegeo::dv3& viewpointEcef) const
            {
                if (!m_enabled)
                {
                    return false;
                }
                
                if (!m_searchResultsExist)
                {
                    return false;
                }
                
                if (m_queriesPending != 0)
                {
                    return false;
                }
                
                if (m_cameraTransitionsController.IsTransitioning())
                {
                    return false;
                }
                
                if (m_secondsSincePreviousRefresh < m_minimumSecondsBetweenUpdates)
                {
                    return false;
                }
                
                
                const float viewpointDistance = (viewpointEcef - interestPointEcef).Length();
                
                const float distanceRatio = std::min(viewpointDistance, m_previousQueryInterestDistance) / std::max(viewpointDistance, m_previousQueryInterestDistance);
                if (distanceRatio < 0.75)
                {
                    return true;
                }
                
                
                const float angularInterestDeltaFromQuery = (interestPointEcef - m_previousQueryLocationEcef).Length() / viewpointDistance;
                
                const float minimumInterestLateralDeltaAngle = m_minimumInterestLateralDeltaAt1km * 0.001f;
                const bool belowLateralThreshold = (angularInterestDeltaFromQuery < minimumInterestLateralDeltaAngle);
                if (belowLateralThreshold)
                {
                    return false;
                }
                
                const float angularInterestDelta = (interestPointEcef - m_previousInterestEcefLocation).Length() / viewpointDistance;
                const float maxInterestAngularSpeed = m_maximumInterestLateralSpeedAt1km * 0.001f;
                const bool aboveSpeedThreshold = angularInterestDelta > maxInterestAngularSpeed*deltaSeconds;
                if (aboveSpeedThreshold)
                {
                    return false;
                }
                
                return true;
            }


            void SearchRefreshService::TryRefreshSearch(float deltaSeconds, const Eegeo::dv3& interestPointEcef, const Eegeo::dv3& viewpointEcef)
            {
                m_secondsSincePreviousRefresh += deltaSeconds;
                
                bool shouldRefresh = ShouldRefreshSearch(deltaSeconds, interestPointEcef, viewpointEcef);
                
                if(m_previousQueryInterestDistance == 0.0f)
                {
                    shouldRefresh = false;
                }
                
                if (shouldRefresh)
                {
//                    const Eegeo::Space::LatLongAltitude& currentLocation = Eegeo::Space::LatLongAltitude::FromECEF(interestPointEcef);
                    const SearchQuery& previousQuery = m_searchQueryPerformer.GetPreviousSearchQuery();
//                    m_searchQueryPerformer.PerformSearchQuery(previousQuery.Query(), previousQuery.IsCategory(), currentLocation);
                    m_searchQueryPerformer.PerformSearchQuery(previousQuery.Query(), previousQuery.IsCategory(),false);
                    
                    m_previousQueryLocationEcef = interestPointEcef;
                    m_secondsSincePreviousRefresh = 0.f;
                }
                
                m_previousQueryInterestDistance = (viewpointEcef - interestPointEcef).Length();
                m_previousInterestEcefLocation = interestPointEcef;
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

