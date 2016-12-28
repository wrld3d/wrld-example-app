// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Search.h"
#include "ICallback.h"
#include "IdentitySearchCallbackData.h"
#include "SearchResultModel.h"
#include "Yelp.h"
#include "IWebLoadRequestFactory.h"
#include "SearchTagToYelpCategoryMapper.h"

#include "liboauthcpp.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                class YelpSearchQueryFactory
                {
                public:
                    YelpSearchQueryFactory(
                        const std::string& yelpConsumerKey,
                        const std::string& yelpConsumerSecret,
                        const std::string& yelpOAuthToken,
                        const std::string& yelpOAuthTokenSecret,
                        SdkModel::SearchTagToYelpCategoryMapper& searchTagToYelpCategoryMap,
                        Eegeo::Web::IWebLoadRequestFactory& webRequestFactory);
                    
                    ~YelpSearchQueryFactory();
                    
                    IYelpSearchQuery* CreateYelpSearchForQuery(const Search::SdkModel::SearchQuery& query,
                                                               Eegeo::Helpers::ICallback0& completionCallback);
                    
                private:
                    const std::string m_apiUrl;
                    
                    OAuth::Consumer m_consumer;
                    OAuth::Client m_client;
                    OAuth::Token m_token;
                    
                    Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
                    SdkModel::SearchTagToYelpCategoryMapper& m_searchTagToYelpCategoryMap;
                };
            }
        }
    }
}
