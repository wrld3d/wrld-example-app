// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"
#include "Search.h"
#include "Yelp.h"
#include "Web.h"
#include "ICallback.h"

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
                                             const std::string& yelpApiKey,
                                             const YelpBusinessJsonParser& yelpBusinessParser,
                                             Eegeo::Web::IWebLoadRequestFactory& webRequestFactory);
                    
                    virtual ~YelpBusinessQueryFactory() {;}
                    
                    virtual YelpBusinessQuery* Create(const std::string& searchEntityId,
                                                      Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& completionCallback);
                    
                private:
                    const std::string m_apiUrl;
                    const std::string m_yelpApiKey;
                    
                    const YelpBusinessJsonParser& m_yelpBusinessParser;
                    Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
                };
            }
        }
    }
}