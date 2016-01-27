// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ExampleAppCustomWebLoadRequestFactory.h"
#include "WebRequestBuilder.h"

namespace ExampleApp
{
    namespace Net
    {
        namespace SdkModel
        {
            ExampleAppCustomWebLoadRequestFactory::ExampleAppCustomWebLoadRequestFactory(Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory,
                                                                                         INetworkCapabilities& networkCapabilities)
            : m_webLoadRequestFactory(webLoadRequestFactory)
            , m_networkCapabilities(networkCapabilities)
            {
                
            }
            
            Eegeo::Web::WebRequestBuilder ExampleAppCustomWebLoadRequestFactory::Begin(const Eegeo::Web::HttpVerbs::Values httpVerb,
                                                const std::string& url,
                                                Eegeo::Web::IWebLoadRequestCompletionCallback& callback)
            {
                Eegeo::Web::WebRequestBuilder builder = m_webLoadRequestFactory.Begin(httpVerb, url, callback);
                if (!CanStream())
                {
                    builder.SetShouldRequestOnlyFromCache(true);
                }
                return builder;
            }
            
            bool ExampleAppCustomWebLoadRequestFactory::CanStream()
            {
                const bool dontRequireWifi = !m_networkCapabilities.StreamOverWifiOnly();
                const bool haveWifi = m_networkCapabilities.ConnectedToWifi();
                const bool haveNetwork = m_networkCapabilities.NetworkAvailable();
                
                if (haveWifi || (haveNetwork && dontRequireWifi))
                {
                    return true;
                }
                
                return false;
            }
        }
    }
}
