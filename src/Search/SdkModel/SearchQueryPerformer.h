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
                ExampleAppMessaging::TMessageBus& m_messageBus;

            public:
                SearchQueryPerformer(ISearchService& exteriorSearchService,
                                     ISearchResultRepository& searchResultRepository,
                                     ExampleApp::AppCamera::SdkModel::IAppCameraController& cameraController,
                                     ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchQueryPerformer();

                bool HasQuery() const;

                const SearchQuery& GetPreviousSearchQuery() const
                {
                    return m_previousQuery;
                }

                void PerformSearchQuery(const std::string& query, bool isTag, bool tryInteriorSearch, const std::string& interiorId = "");
                void PerformSearchQuery(const std::string& query, bool isTag, bool tryInteriorSearch, float radius, const std::string& interiorId = "");
                void PerformSearchQuery(const std::string& query, bool isTag, bool tryInteriorSearch, const Eegeo::Space::LatLongAltitude& location, bool startAtGPSLocation=false, const std::string& interiorId = "");
                void PerformSearchQuery(const std::string& query, bool isTag, bool tryInteriorSearch, const Eegeo::Space::LatLongAltitude& location, float radius, bool startAtGPSLocation=false, const std::string& interiorId = "");

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

