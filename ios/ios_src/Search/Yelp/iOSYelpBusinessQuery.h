// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "IYelpSearchQuery.h"
#include "Types.h"
#include "ICallback.h"
#include "IdentitySearchCallbackData.h"
#include "IYelpCategoryMapper.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            class iOSYelpBusinessQuery : public IYelpSearchQuery, private Eegeo::NonCopyable
            {
            public:
                iOSYelpBusinessQuery(const std::string& yelpConsumerKey,
                                     const std::string& yelpConsumerSecret,
                                     const std::string& yelpOAuthToken,
                                     const std::string& yelpOAuthTokenSecret,
                                     IYelpCategoryMapper& yelpCategoryMapper,
                                     const std::string& locationIdentifier,
                                     Eegeo::Helpers::ICallback1<const SdkModel::IdentitySearchCallbackData&>& callback,
                                     SdkModel::ISearchResultParser& searchResultParser);
                
                ~iOSYelpBusinessQuery();
                
                void Dispatch();
                
                void Cancel();
                
                bool IsSucceeded();
                
                const std::string& ResponseString();
                
                const std::vector<SdkModel::SearchResultModel>& ResponseSearchQueryResults();
                
                
            private:
                void DispatchCallback();
                
                std::string m_yelpConsumerKey;
                std::string m_yelpConsumerSecret;
                std::string m_yelpOAuthToken;
                std::string m_yelpOAuthTokenSecret;
                IYelpCategoryMapper& m_yelpCategoryMapper;
                std::string m_locationIdentifier;
                Eegeo::Helpers::ICallback1<const SdkModel::IdentitySearchCallbackData&>& m_callback;
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
