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
            namespace SdkModel
            {
            class YelpSearchService : public Search::SdkModel::SearchServiceBase, private Eegeo::NonCopyable
            {
            private:
                std::shared_ptr<YelpSearchQueryFactory> m_searchQueryFactory;
                std::shared_ptr<YelpBusinessQueryFactory> m_yelpBusinessQueryFactory;
                
                std::shared_ptr<Search::SdkModel::ISearchResultParser> m_searchResultParser;
                std::shared_ptr<Net::SdkModel::INetworkCapabilities> m_networkCapabilities;
                
                Search::SdkModel::SearchQuery m_currentQueryModel;
                Eegeo::Helpers::TCallback0<YelpSearchService> m_poiSearchCallback;
                IYelpSearchQuery* m_pCurrentRequest;
                bool m_hasActiveQuery;
                
            public:
                YelpSearchService(const std::shared_ptr<YelpSearchQueryFactory>& searchQueryFactory,
                                  const std::shared_ptr<YelpBusinessQueryFactory>& yelpBusinessQueryFactory,
                                  const std::shared_ptr<Search::SdkModel::ISearchResultParser>& searchResultParser,
                                  const std::shared_ptr<Net::SdkModel::INetworkCapabilities>& networkCapabilities,
                                  const std::vector<std::string>& handledTags);
                
                ~YelpSearchService();
                
                void CancelInFlightQueries();
                
                void PerformLocationQuerySearch(const Search::SdkModel::SearchQuery& query);
                
                void PerformIdentitySearch(const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                           Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback);
                
            private:
            
                
                void HandleSearchResponse();
                
                void HandleYelpBusinessQueryDestroy(YelpBusinessQuery& yelpBusinessQuery);
            };
        }
        }
    }
}

