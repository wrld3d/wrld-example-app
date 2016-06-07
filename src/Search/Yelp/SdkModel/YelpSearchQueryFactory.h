// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"
#include "ICallback.h"
#include "IdentitySearchCallbackData.h"
#include "SearchResultModel.h"
#include "Yelp.h"
#include "IWebLoadRequestFactory.h"

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
                    std::string m_yelpConsumerKey;
                    std::string m_yelpConsumerSecret;
                    std::string m_yelpOAuthToken;
                    std::string m_yelpOAuthTokenSecret;
                    Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;

                public:
                    YelpSearchQueryFactory(
                        const std::string& yelpConsumerKey,
                        const std::string& yelpConsumerSecret,
                        const std::string& yelpOAuthToken,
                        const std::string& yelpOAuthTokenSecret,
                        Eegeo::Web::IWebLoadRequestFactory& webRequestFactory);
                    
                    ~YelpSearchQueryFactory();
                    
                    IYelpSearchQuery* CreateYelpSearchForQuery(const Search::SdkModel::SearchQuery& query,
                                                                       Eegeo::Helpers::ICallback0& completionCallback);
                    
                };
            }
        }
    }
}
