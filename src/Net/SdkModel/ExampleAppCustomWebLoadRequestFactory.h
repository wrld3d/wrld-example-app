// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include <string>
#include "Types.h"
#include "Web.h"
#include "IHttpCache.h"
#include "IWebLoadRequest.h"
#include "IWebLoadRequestFactory.h"
#include "WebLoadRequestCompletionCallback.h"
#include "INetworkCapabilities.h"

namespace ExampleApp
{
    namespace Net
    {
        namespace SdkModel
        {
            class ExampleAppCustomWebLoadRequestFactory : public Eegeo::Web::IWebLoadRequestFactory
            {
                Eegeo::Web::IWebLoadRequestFactory& m_webLoadRequestFactory;
                INetworkCapabilities& m_networkCapabilities;
                
            public:
                ExampleAppCustomWebLoadRequestFactory(Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory,
                                                      INetworkCapabilities& networkCapabilities);
                
                
                Eegeo::Web::WebRequestBuilder Begin(const Eegeo::Web::HttpVerbs::Values httpVerb,
                                                     const std::string& url,
                                                     Eegeo::Web::IWebLoadRequestCompletionCallback& callback);
                
            private:
                bool CanStream();
                
            };
        }
    }
}


