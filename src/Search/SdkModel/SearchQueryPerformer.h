// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include "Types.h"
#include "Search.h"
#include "ISearchQueryPerformer.h"
#include "Location.h"
#include "CallbackCollection.h"
#include "ICallback.h"
#include "SearchQuery.h"
#include "IAppCameraController.h"
#include "BidirectionalBus.h"
#include "CameraTransitions.h"
#include "ApplicationConfig.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            class SearchQueryPerformer : public ISearchQueryPerformer, private Eegeo::NonCopyable
            {
                ISearchService& m_searchService;
                
                ISearchResultRepository& m_searchResultsRepository;
                Eegeo::Helpers::ICallback2<const SearchQuery&, const std::vector<SearchResultModel>&>* m_pSearchResultResponseReceivedCallback;
                Eegeo::Helpers::CallbackCollection0 m_queryResultsClearedCallbacks;
                SearchQuery m_previousQuery;
                bool m_hasQuery;
                ExampleApp::AppCamera::SdkModel::IAppCameraController& m_cameraController;
                CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionsController;
                bool m_isBuildingsViewAvailable;
                Eegeo::dv3 m_buildingsViewLocationECEF;
                float m_buildingsViewDistanceToInterest;
                float m_buildingsViewHeadingRadians;
                ExampleAppMessaging::TMessageBus& m_messageBus;

            public:
                SearchQueryPerformer(ISearchService& exteriorSearchService,
                                     ISearchResultRepository& searchResultRepository,
                                     ExampleApp::AppCamera::SdkModel::IAppCameraController& cameraController,
                                     CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionsController,
                                     ExampleApp::ApplicationConfig::ApplicationConfiguration& appConfig,
                                     ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchQueryPerformer();

                bool HasQuery() const;

                const SearchQuery& GetPreviousSearchQuery() const
                {
                    return m_previousQuery;
                }

                void PerformSearchQuery(const std::string& query, bool isTag, bool tryInteriorSearch, bool shouldZoomToBuildingsView);
                void PerformSearchQuery(const std::string& query, bool isTag, bool tryInteriorSearch, bool shouldZoomToBuildingsView, float radius);
                void PerformSearchQuery(const std::string& query, bool isTag, bool tryInteriorSearch, bool shouldZoomToBuildingsView, const Eegeo::Space::LatLongAltitude& location);
                void PerformSearchQuery(const std::string& query, bool isTag, bool tryInteriorSearch, bool shouldZoomToBuildingsView, const Eegeo::Space::LatLongAltitude& location, float radius);

                void RemoveSearchQueryResults();

                void InsertOnSearchResultsClearedCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveOnSearchResultsClearedCallback(Eegeo::Helpers::ICallback0& callback);

            private:

                void RemoveExistingSearchResults();

                void HandleSearchResultsResponseReceived(
                        const SearchQuery& query,
                        const std::vector<SearchResultModel>& results);

            };
        }
    }
}

