// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IYelpSearchQuery.h"
#include "Types.h"
#include "SearchQuery.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            class iOSYelpSearchQuery : public IYelpSearchQuery, private Eegeo::NonCopyable
            {
            public:
                iOSYelpSearchQuery(const std::string& yelpConsumerKey,
                                   const std::string& yelpConsumerSecret,
                                   const std::string& yelpOAuthToken,
                                   const std::string& yelpOAuthTokenSecret,
                                   const SdkModel::SearchQuery& searchQuery,
                                   Eegeo::Helpers::ICallback0& completionCallback,
                                   SdkModel::ISearchResultParser& searchResultParser);
                
                ~iOSYelpSearchQuery();
                
                void Dispatch();
                
                void Cancel();
                
                bool IsSucceeded();
                
                const std::string& ResponseString();
                
                const SdkModel::SearchQuery& GetSearchQuery() const;
                
                const std::vector<SdkModel::SearchResultModel>& ResponseSearchQueryResults();
                
            private:
                std::string m_yelpConsumerKey;
                std::string m_yelpConsumerSecret;
                std::string m_yelpOAuthToken;
                std::string m_yelpOAuthTokenSecret;
                SdkModel::SearchQuery m_searchQuery;
                Eegeo::Helpers::ICallback0& m_completionCallback;
                std::string m_responseString;
                std::vector<SdkModel::SearchResultModel> m_responseQueryResults;
                bool m_cancelled;
                bool m_isSuccess;
                NSURLSessionDataTask* m_pTask;
                SdkModel::ISearchResultParser& m_searchResultParser;
            };
        }
    }
}
