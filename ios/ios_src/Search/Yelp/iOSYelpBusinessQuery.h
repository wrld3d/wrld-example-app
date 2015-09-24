// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "IYelpSearchQuery.h"
#include "Types.h"
#include "ICallback.h"
#include "IdentitySearchCallbackData.h"
#include "IYelpCategoryMapper.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            class iOSYelpBusinessQuery : public SdkModel::IYelpSearchQuery, private Eegeo::NonCopyable
            {
            public:
                iOSYelpBusinessQuery(const std::string& yelpConsumerKey,
                                     const std::string& yelpConsumerSecret,
                                     const std::string& yelpOAuthToken,
                                     const std::string& yelpOAuthTokenSecret,
                                     SdkModel::IYelpCategoryMapper& yelpCategoryMapper,
                                     const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                     Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback);
                
                ~iOSYelpBusinessQuery();
                
                void Dispatch();
                
                void Cancel();
                
                bool IsSucceeded();
                
                const std::string& ResponseString();
                
            private:
                void DispatchCallback();
                
                std::string m_yelpConsumerKey;
                std::string m_yelpConsumerSecret;
                std::string m_yelpOAuthToken;
                std::string m_yelpOAuthTokenSecret;
                SdkModel::IYelpCategoryMapper& m_yelpCategoryMapper;
                Search::SdkModel::SearchResultModel m_outdatedSearchResult;
                Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& m_callback;
                std::string m_responseString;
                bool m_cancelled;
                bool m_isSuccess;
                NSURLSessionDataTask* m_pTask;
            };
        }
    }
}
