// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchRefreshService.h"
#include "ISearchService.h"
#include "ISearchQueryPerformer.h"
#include "LatLongAltitude.h"
#include "ICameraTransitionController.h"
#include "InteriorInteractionModel.h"
#include "InteriorsModel.h"

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
                    Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                    float minimumSecondsBetweenUpdates,
                    float minimumInterestLateralDeltaAt1km,
                    float minimumInteriorInterestLateralDelta,
                    float maximumInterestLateralSpeedAt1km)
                : m_minimumSecondsBetweenUpdates(minimumSecondsBetweenUpdates)
                , m_minimumInterestLateralDeltaAt1km(minimumInterestLateralDeltaAt1km)
                , m_minimumInteriorInterestLateralDelta(minimumInteriorInterestLateralDelta)
                , m_maximumInterestLateralSpeedAt1km(maximumInterestLateralSpeedAt1km)
                , m_searchService(searchService)
                , m_searchQueryPerformer(searchQueryPerformer)
                , m_cameraTransitionsController(cameraTransitionsController)
                , m_interiorInteractionModel(interiorInteractionModel)
                , m_searchResultQueryIssuedCallback(this, &SearchRefreshService::HandleSearchQueryIssued)
                , m_searchResultResponseReceivedCallback(this, &SearchRefreshService::HandleSearchResultsResponseReceived)
                , m_searchQueryResultsClearedCallback(this, &SearchRefreshService::HandleSearchQueryResultsCleared)
                , m_interiorChangedCallback(this, &SearchRefreshService::HandleInteriorChanged)
                , m_queriesPending(0)
                , m_searchResultsExist(false)
                , m_searchResultsCleared(false)
                , m_secondsSincePreviousRefresh(0.f)
                , m_enabled(true)
                , m_previousQueryFloorIndex(0)
                , m_previousQueryLocationEcef(Eegeo::dv3::Zero())
                , m_previousInterestEcefLocation(Eegeo::dv3::Zero())
                , m_previousQueryInterestDistance(0.f)
                , m_previousQueryInteriorId()
                , m_interiorHasChanged(false)
            {
                m_searchService.InsertOnPerformedQueryCallback(m_searchResultQueryIssuedCallback);
                m_searchService.InsertOnReceivedQueryResultsCallback(m_searchResultResponseReceivedCallback);
                m_searchQueryPerformer.InsertOnSearchResultsClearedCallback(m_searchQueryResultsClearedCallback);
                m_interiorInteractionModel.RegisterModelChangedCallback(m_interiorChangedCallback);
            }

            SearchRefreshService::~SearchRefreshService()
            {
                m_interiorInteractionModel.UnregisterModelChangedCallback(m_interiorChangedCallback);
                m_searchQueryPerformer.RemoveOnSearchResultsClearedCallback(m_searchQueryResultsClearedCallback);
                m_searchService.RemoveOnReceivedQueryResultsCallback(m_searchResultResponseReceivedCallback);
                m_searchService.RemoveOnPerformedQueryCallback(m_searchResultQueryIssuedCallback);
            }

            void SearchRefreshService::SetEnabled(bool enabled)
            {
                m_enabled = enabled;
            }
            
            bool SearchRefreshService::ShouldRefreshSearch(float deltaSeconds, const Eegeo::dv3& interestPointEcef, const Eegeo::dv3& viewpointEcef)
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

                bool hasChangedInteriorFloors = m_interiorInteractionModel.HasInteriorModel() &&
                m_previousQueryFloorIndex != m_interiorInteractionModel.GetSelectedFloorIndex();
                if (hasChangedInteriorFloors)
                {
                    if (m_interiorHasChanged)
                    {
                        m_interiorHasChanged = false;

                        m_previousQueryFloorIndex = m_interiorInteractionModel.GetSelectedFloorIndex();

                        return false;
                    }

                    
                    return true;
                }
                
                const double viewpointDistance = (viewpointEcef - interestPointEcef).Length();

                const double distanceRatio = std::min(viewpointDistance, m_previousQueryInterestDistance) / std::max(viewpointDistance, m_previousQueryInterestDistance);
                if (distanceRatio < 0.75)
                {
                    return true;
                }
                
                const double angularInterestDeltaFromQuery = (interestPointEcef - m_previousQueryLocationEcef).Length() / viewpointDistance;
                const double multiplier = 0.001;
                const double minimumInterestLateralDeltaAngle = m_interiorInteractionModel.HasInteriorModel() ? m_minimumInteriorInterestLateralDelta * m_minimumInteriorInterestLateralDelta : m_minimumInterestLateralDeltaAt1km * multiplier;

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

                if (m_previousQueryInterestDistance == 0.0f)
                {
                    shouldRefresh = false;
                }
                
                if (shouldRefresh)
                {
                    const Eegeo::Space::LatLongAltitude& currentLocation = Eegeo::Space::LatLongAltitude::FromECEF(interestPointEcef);
                    const SearchQuery& previousQuery = m_searchQueryPerformer.GetPreviousSearchQuery();
                    m_searchQueryPerformer.PerformSearchQuery(previousQuery.Query(), previousQuery.IsCategory(), previousQuery.ShouldTryInteriorSearch(), currentLocation);

                    if (m_interiorInteractionModel.HasInteriorModel())
                    {
                        m_previousQueryInteriorId = m_interiorInteractionModel.GetInteriorModel()->GetId();
                        m_previousQueryFloorIndex = m_interiorInteractionModel.GetSelectedFloorIndex();
                    }

                    m_previousQueryLocationEcef = interestPointEcef;
                    m_secondsSincePreviousRefresh = 0.f;
                }

                m_previousQueryInterestDistance = (viewpointEcef - interestPointEcef).Length();
                m_previousInterestEcefLocation = interestPointEcef;
            }

            void SearchRefreshService::HandleInteriorChanged()
            {
                if (!m_searchResultsCleared && m_searchResultsExist)
                {
                    const SearchQuery& previousQuery = m_searchQueryPerformer.GetPreviousSearchQuery();
                    
                    if (previousQuery.IsCategory())
                    {
                        m_searchQueryPerformer.PerformSearchQuery(previousQuery.Query(), previousQuery.IsCategory(), previousQuery.ShouldTryInteriorSearch());
                        m_secondsSincePreviousRefresh = 0.f;

                        m_interiorHasChanged = true;
                    }
                }
            }

            void SearchRefreshService::HandleSearchQueryIssued(const SearchQuery& query)
            {
                ++ m_queriesPending;
                m_searchResultsCleared = false;
                m_previousQueryFloorIndex = m_interiorInteractionModel.GetSelectedFloorIndex();
            }

            void SearchRefreshService::HandleSearchResultsResponseReceived(const SearchQuery& query,
                    const std::vector<SearchResultModel>& results)
            {
                if (!m_searchResultsCleared)
                {
                    m_searchResultsExist = true;
                }
                m_previousQueryLocationEcef = query.Location().ToECEF();
                -- m_queriesPending;
                Eegeo_ASSERT(m_queriesPending >= 0);
            }

            void SearchRefreshService::HandleSearchQueryResultsCleared()
            {
                m_searchResultsCleared = true;
                m_searchResultsExist = false;
            }
        }
    }
}

