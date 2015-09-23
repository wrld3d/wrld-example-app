// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include <string>
#include <vector>
#include "Search.h"
#include "SearchQuery.h"
#include "SearchResultModel.h"
#include "SearchServiceBase.h"
#include "ICallback.h"
#include "CategorySearchModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Combined
        {
            class CombinedSearchService
            : public SdkModel::SearchServiceBase
            {
            public:
                
                CombinedSearchService(const std::map<std::string,SdkModel::ISearchService*>& searchServices);
                
                ~CombinedSearchService();
                
                bool CanHandleCategory(const std::string& category) const;
                
                void CancelInFlightQueries();
                
                void PerformLocationQuerySearch(const SdkModel::SearchQuery& query);
                
                void PerformIdentitySearch(const SdkModel::SearchResultModel& outdatedSearchResult,
                                           Eegeo::Helpers::ICallback1<const SdkModel::IdentitySearchCallbackData&>& callback);
                
            private:
                
                void OnSearchResponseRecieved(const SdkModel::SearchQuery& query, const std::vector<SdkModel::SearchResultModel>& results);
                
                
            private:
                
                std::map<std::string,SdkModel::ISearchService*> m_searchServices;
                
                Eegeo::Helpers::TCallback2<CombinedSearchService,
                                           const SdkModel::SearchQuery&,
                                           const std::vector<SdkModel::SearchResultModel>&> m_searchQueryResponseCallback;
                
                int m_pendingResultsLeft;
                std::vector<SdkModel::SearchResultModel> m_combinedResults;
                SdkModel::SearchQuery m_currentQueryModel;
                bool m_hasActiveQuery;
                
            };
        }
    }
}
