// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NetworkCapabilities.h"
#include "IPersistentSettingsModel.h"

namespace
{
    const std::string NetworkCapabilities_OnlyStreamOverWifi_Key = "NetworkCapabilities_OnlyStreamOverWifi_Key";
    const std::string NetworkCapabilities_HttpCacheEnabled_Key = "NetworkCapabilities_HttpCacheEnabled_Key";
}

namespace ExampleApp
{
    namespace Net
    {
        namespace SdkModel
        {
            NetworkCapabilities::NetworkCapabilities(Eegeo::Web::IConnectivityService& connectivityService,
                                                     Eegeo::Helpers::IHttpCache& httpCache,
                                                     PersistentSettings::IPersistentSettingsModel& persistentSettings)
            : m_connectivityService(connectivityService)
            , m_httpCache(httpCache)
            , m_persistentSettings(persistentSettings)
            {
                if(!m_persistentSettings.TryGetValue(NetworkCapabilities_OnlyStreamOverWifi_Key, m_streamOverWifiOnly))
                {
                    m_streamOverWifiOnly = false;
                }
                
                bool httpCachingEnabled;
                if(m_persistentSettings.TryGetValue(NetworkCapabilities_HttpCacheEnabled_Key, httpCachingEnabled))
                {
                    SetHttpCachingEnabled(httpCachingEnabled);
                }
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
                m_persistentSettings.SetValue(NetworkCapabilities_OnlyStreamOverWifi_Key, m_streamOverWifiOnly);
            }
            
            bool NetworkCapabilities::HttpCachingEnabled() const
            {
                return m_httpCache.GetEnabled();
            }
            
            void NetworkCapabilities::SetHttpCachingEnabled(bool httpCachingEnabled)
            {
                m_httpCache.SetEnabled(httpCachingEnabled);
                m_persistentSettings.SetValue(NetworkCapabilities_HttpCacheEnabled_Key, httpCachingEnabled);
            }
        }
    }
}
