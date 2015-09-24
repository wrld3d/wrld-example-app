// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include <string>
#include "Search.h"
#include "SearchServiceBase.h"
#include "Types.h"
#include "ICallback.h"
#include "Yelp.h"
#include "Web.h"
#include "SearchQuery.h"
#include "WebLoadRequestCompletionCallback.h"
#include "SearchResultModel.h"
#include "NetIncludes.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            class YelpSearchService : public SdkModel::SearchServiceBase, private Eegeo::NonCopyable
            {
            private:
                IYelpSearchQueryFactory& m_searchQueryFactory;
                SdkModel::ISearchResultParser& m_searchResultParser;
                Net::SdkModel::INetworkCapabilities& m_networkCapabilities;
                
                SdkModel::SearchQuery m_currentQueryModel;
                Eegeo::Helpers::TCallback0<YelpSearchService> m_poiSearchCallback;
                IYelpSearchQuery* m_pCurrentRequest;
                bool m_hasActiveQuery;
                
            public:
                YelpSearchService(IYelpSearchQueryFactory& searchQueryFactory,
                                  SdkModel::ISearchResultParser& searchResultParser,
                                  Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                  const std::vector<std::string>& availableCategories);
                
                ~YelpSearchService();
                
                void CancelInFlightQueries();
                
                void PerformLocationQuerySearch(const SdkModel::SearchQuery& query);
                
                void PerformIdentitySearch(const SdkModel::SearchResultModel& outdatedSearchResult,
                                           Eegeo::Helpers::ICallback1<const SdkModel::IdentitySearchCallbackData&>& callback);
                
            private:
                
                void HandleSearchResponse();
            };
        }
    }
}

