// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "Search.h"
#include "Yelp.h"
#include "Web.h"
#include "ICallback.h"
#include "ApplicationConfiguration.h"
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
                    YelpBusinessQueryFactory(const std::shared_ptr<ExampleApp::ApplicationConfig::ApplicationConfiguration>& config,
                                             const std::shared_ptr<YelpBusinessJsonParser>& yelpBusinessParser,
                                             const std::shared_ptr<Eegeo::Web::IWebLoadRequestFactory>& webRequestFactory
                                             );
                    
                    virtual ~YelpBusinessQueryFactory() {;}
                    
                    virtual YelpBusinessQuery* Create(const std::string& searchEntityId,
                                                      Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& completionCallback);
                    
                private:
                    const std::string m_apiUrl;
                    
                    OAuth::Consumer m_consumer;
                    OAuth::Client m_client;
                    OAuth::Token m_token;

                    
                    std::shared_ptr<const YelpBusinessJsonParser> m_yelpBusinessParser;
                    std::shared_ptr<Eegeo::Web::IWebLoadRequestFactory> m_webRequestFactory;
                };
            }
        }
    }
}