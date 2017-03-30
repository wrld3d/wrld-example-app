// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "Search.h"
#include "Space.h"
#include "ISearchRefreshService.h"
#include "ICallback.h"
#include "SearchQuery.h"
#include "CameraTransitions.h"
#include "VectorMath.h"
#include "Interiors.h"
#include "InteriorId.h"
#include "ITagSearchRepository.h"
#include "InteriorMenuObserver.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            class SearchRefreshService : public ISearchRefreshService, private Eegeo::NonCopyable
            {
                const float m_minimumSecondsBetweenUpdates;
                const float m_minimumInterestLateralDeltaAt1km;
                const float m_minimumInteriorInterestLateralDelta;
                const float m_maximumInterestLateralSpeedAt1km;

                ISearchService& m_searchService;
                
                ISearchQueryPerformer& m_searchQueryPerformer;
                InteriorMenuObserver& m_interiorMenuObserver;
                CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionsController;
                Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                Eegeo::Helpers::TCallback1<SearchRefreshService, const SearchQuery&> m_searchResultQueryIssuedCallback;
                Eegeo::Helpers::TCallback2<SearchRefreshService, const SearchQuery&, const std::vector<SearchResultModel>&> m_searchResultResponseReceivedCallback;
                Eegeo::Helpers::TCallback0<SearchRefreshService> m_searchQueryResultsClearedCallback;
                Eegeo::Helpers::TCallback0<SearchRefreshService> m_interiorTagsUpdatedCallback;
                Eegeo::Helpers::TCallback0<SearchRefreshService> m_interiorModelChangedCallback;
                int m_queriesPending;
                bool m_searchResultsExist;
                bool m_searchResultsCleared;
                float m_secondsSincePreviousRefresh;
                Eegeo::dv3 m_previousQueryLocationEcef;
                Eegeo::dv3 m_previousInterestEcefLocation;
                double m_previousQueryInterestDistance;
                bool m_enabled;
                int m_previousQueryFloorIndex;
                bool m_interiorHasChanged;
                Eegeo::Resources::Interiors::InteriorId m_previousQueryInteriorId;

            public:
                SearchRefreshService(ISearchService& searchService,
                                     ISearchQueryPerformer& searchQueryPerformer,
                                     CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionsController,
                                     Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                     TagSearch::View::ITagSearchRepository& tagSearchRepository,
                                     float minimumSecondsBetweenUpdates,
                                     float minimumInterestLateralDeltaAt1km,
                                     float minimumInteriorInterestLateralDelta,
                                     float maximumInterestLateralSpeedAt1km,
                                     InteriorMenuObserver& interiorMenuObserver);

                ~SearchRefreshService();

                void TryRefreshSearch(float deltaSeconds, const Eegeo::dv3& interestPointEcef, const Eegeo::dv3& viewpointEcef);
                void SetAnchorPoint(const Eegeo::dv3& interestPointEcef);
                void SetEnabled(bool enabled);
                const bool IsEnabled() const
                {
                    return m_enabled;
                }

            private:
                void HandleInteriorTagsChanged();
                void HandleInteriorModelChanged();

                void HandleSearchQueryIssued(const SearchQuery& query);

                void HandleSearchResultsResponseReceived(const SearchQuery& query,
                        const std::vector<SearchResultModel>& results);

                void HandleSearchQueryResultsCleared();
                
                bool ShouldRefreshSearch(float deltaSeconds, const Eegeo::dv3& interestPointEcef, const Eegeo::dv3& viewpointEcef);
                
                bool TagStillPresent(const SearchQuery& previousQuery);
                
                TagSearch::View::ITagSearchRepository& m_tagSearchRepository;
            };
        }
    }
}

