// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "Search.h"
#include "Yelp.h"
#include "Web.h"
#include "ICallback.h"
#include "liboauthcpp.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                class YelpBusinessQueryFactory : private Eegeo::NonCopyable
                {
                public:
                    YelpBusinessQueryFactory(
                                             const std::string& yelpConsumerKey,
                                             const std::string& yelpConsumerSecret,
                                             const std::string& yelpOAuthToken,
                                             const std::string& yelpOAuthTokenSecret,
                                             const YelpBusinessJsonParser& yelpBusinessParser,
                                             Eegeo::Web::IWebLoadRequestFactory& webRequestFactory);
                    
                    virtual ~YelpBusinessQueryFactory() {;}
                    
                    virtual YelpBusinessQuery* Create(const std::string& searchEntityId,
                                                      Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& completionCallback);
                    
                private:
                    const std::string m_apiUrl;
                    
                    OAuth::Consumer m_consumer;
                    OAuth::Client m_client;
                    OAuth::Token m_token;

                    
                    const YelpBusinessJsonParser& m_yelpBusinessParser;
                    Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
                };
            }
        }
    }
}