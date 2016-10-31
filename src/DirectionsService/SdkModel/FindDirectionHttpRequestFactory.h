// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "FindDirectionQuery.h"
#include "IWebLoadRequestFactory.h"
#include "FindDirectionHttpRequest.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
        
            class FindDirectionHttpRequestFactory
            {
            public:
                FindDirectionHttpRequestFactory(const std::string& eeGeoApiKey,
                                                Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder);
                
                ~FindDirectionHttpRequestFactory();
                
                FindDirectionHttpRequest* CreateFindDirectionQuery(const FindDirectionQuery& query,
                                                           Eegeo::Helpers::ICallback0& completionCallback);
                
            private:
                
                const std::string m_apiUrl;
                const std::string m_eegeoApiKey;
                Eegeo::Helpers::UrlHelpers::IUrlEncoder& m_urlEncoder;
                Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
                
            };
        }
    }
}