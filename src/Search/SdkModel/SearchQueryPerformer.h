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
#include "GpsGlobeCameraController.h"

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
                Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& m_cameraController;                

            public:
                SearchQueryPerformer(ISearchService& exteriorSearchService,
                                     ISearchResultRepository& searchResultRepository,
                                     Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& cameraController);

                ~SearchQueryPerformer();

                bool HasQuery() const;

                const SearchQuery& GetPreviousSearchQuery() const
                {
                    return m_previousQuery;
                }

                void PerformSearchQuery(const std::string& query, bool isCategory, bool tryInteriorSearch);
                void PerformSearchQuery(const std::string& query, bool isCategory, bool tryInteriorSearch, float radius);
                void PerformSearchQuery(const std::string& query, bool isCategory, bool tryInteriorSearch, const Eegeo::Space::LatLongAltitude& location);
                void PerformSearchQuery(const std::string& query, bool isCategory, bool tryInteriorSearch, const Eegeo::Space::LatLongAltitude& location, float radius);

                void RemoveSearchQueryResults();

                void InsertOnSearchResultsClearedCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveOnSearchResultsClearedCallback(Eegeo::Helpers::ICallback0& callback);

            private:

                void RemoveExistingSearchResults();

                void HandleSearchResultsResponseReceived(const SearchQuery& query,
                        const std::vector<SearchResultModel>& results);

            };
        }
    }
}

