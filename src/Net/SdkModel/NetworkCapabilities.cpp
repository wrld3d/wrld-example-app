// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NetworkCapabilities.h"

namespace ExampleApp
{
    namespace Net
    {
        namespace SdkModel
        {
            NetworkCapabilities::NetworkCapabilities(Eegeo::Web::IConnectivityService& connectivityService,
                                                     Eegeo::Helpers::IHttpCache& httpCache,
                                                     bool streamOverWifiOnly)
            : m_connectivityService(connectivityService)
            , m_httpCache(httpCache)
            , m_streamOverWifiOnly(streamOverWifiOnly)
            {
                
            }
            
            bool NetworkCapabilities::StreamOverWifiOnly() const
            {
                return m_streamOverWifiOnly;
            }
            
            bool NetworkCapabilities::ConnectedToWifi() const
            {
                return m_connectivityService.GetConnectivityType() == Eegeo::Web::Wifi;
            }
            
            bool NetworkCapabilities::NetworkAvailable() const
            {
                return m_connectivityService.HasConnectivity();
            }
            
            void NetworkCapabilities::SetStreamOverWifiOnlyMode(bool streamOverWifiOnlyEnabled)
            {
                m_streamOverWifiOnly = streamOverWifiOnlyEnabled;
            }
            
            bool NetworkCapabilities::HttpCachingEnabled() const
            {
                return m_httpCache.GetEnabled();
            }
            
            void NetworkCapabilities::SetHttpCachingEnabled(bool httpCachingEnabled)
            {
                m_httpCache.SetEnabled(httpCachingEnabled);
            }
        }
    }
}
