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
#include "TagSearchModel.h"
#include "Interiors.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Combined
        {
            namespace SdkModel
            {
                class CombinedSearchService : public Search::SdkModel::SearchServiceBase
                {
                public:
                    
                    CombinedSearchService(const std::map<std::string, Search::SdkModel::ISearchService*>& searchServices,
                                          Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel);
                    
                    ~CombinedSearchService();
                    
                    bool CanHandleTag(const std::string& tag) const;
                    
                    void CancelInFlightQueries();
                    
                    void PerformLocationQuerySearch(const Search::SdkModel::SearchQuery& query);
                    
                    void PerformIdentitySearch(const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                               Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback);
                    
                private:
                    
                    void OnSearchResponseRecieved(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results);
                    
                    bool CanPerformLocationQuerySearch(const Search::SdkModel::SearchQuery& query, const Search::SdkModel::ISearchService& searchService) const;
                    
                    
                private:
                    
                    std::map<std::string,Search::SdkModel::ISearchService*> m_searchServices;
                    
                    Eegeo::Helpers::TCallback2<CombinedSearchService,
                                               const Search::SdkModel::SearchQuery&,
                                               const std::vector<Search::SdkModel::SearchResultModel>&> m_searchQueryResponseCallback;
                    
                    int m_pendingResultsLeft;
                    std::vector<Search::SdkModel::SearchResultModel> m_combinedResults;
                    Search::SdkModel::SearchQuery m_currentQueryModel;
                    Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                    bool m_hasActiveQuery;
                    
                };
            }
        }
    }
}
