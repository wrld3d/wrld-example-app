// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchRefreshService.h"
#include "ISearchService.h"
#include "ISearchQueryPerformer.h"
#include "LatLongAltitude.h"
#include "ICameraTransitionController.h"
#include "SwallowSearchConstants.h"
#include "InteriorInteractionModel.h"

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
                    float minimumMetresBetweenUpdates)
                : m_minimumSecondsBetweenUpdates(minimumSecondsBetweenUpdates)
                , m_minimumMetresSquaredBetweenUpdates(minimumMetresBetweenUpdates * minimumMetresBetweenUpdates)
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
                , m_cameraTransitioning(false)
                , m_enabled(true)
                , m_previousQueryFloorIndex(0)
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
                        m_cameraTransitioning = false;
                    }

                    if(m_secondsSincePreviousRefresh >= m_minimumSecondsBetweenUpdates)
                    {
                        Eegeo::Space::LatLongAltitude currentLocation = Eegeo::Space::LatLongAltitude::FromECEF(ecefLocation);

                        double distanceMetresSq = (ecefLocation - m_previousQueryLocationEcef).LengthSq();
                        
                        bool hasChangedInteriorFloors = m_interiorInteractionModel.HasInteriorModel() &&
                            m_previousQueryFloorIndex != m_interiorInteractionModel.GetSelectedFloorIndex();

                        if(distanceMetresSq >= m_minimumMetresSquaredBetweenUpdates || hasChangedInteriorFloors)
                        {
                            m_previousQueryLocationEcef = ecefLocation;
                            const SearchQuery& previousQuery = m_searchQueryPerformer.GetPreviousSearchQuery();
                            if (previousQuery.IsCategory() && previousQuery.Query() == Search::Swallow::SearchConstants::OFFICE_CATEGORY_NAME)
                            {
                                // Bodged for Swallow Office category query.
                                m_searchQueryPerformer.PerformSearchQuery(previousQuery.Query(), previousQuery.IsCategory(), previousQuery.IsInterior(), currentLocation, previousQuery.Radius());
                            }
                            else
                            {
                                m_searchQueryPerformer.PerformSearchQuery(previousQuery.Query(), previousQuery.IsCategory(), previousQuery.IsInterior(), currentLocation);
                            }

                            m_previousQueryFloorIndex = m_interiorInteractionModel.GetSelectedFloorIndex();
                            m_secondsSincePreviousRefresh = 0.f;
                        }
                    }
                }
            }

            void SearchRefreshService::HandleInteriorChanged()
            {
                if (!m_searchResultsCleared && m_searchResultsExist)
                {
                    const SearchQuery& previousQuery = m_searchQueryPerformer.GetPreviousSearchQuery();
                    
                    if (previousQuery.IsCategory())
                    {
                        const bool isInterior = m_interiorInteractionModel.HasInteriorModel();

                        m_searchQueryPerformer.PerformSearchQuery(previousQuery.Query(), previousQuery.IsCategory(), isInterior);
                        m_secondsSincePreviousRefresh = 0.f;
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

