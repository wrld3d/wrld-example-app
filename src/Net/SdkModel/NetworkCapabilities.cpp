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
            , m_streamOverWifiOnly(false)
            , m_networkAvailable(QueryIsNetworkAvailable())
            , m_connectedToWifi(QueryIsConnectedToWifi())
            , m_connectionChangedCallback(this, &NetworkCapabilities::HandleConnectionChanged)
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
                
                m_connectivityService.RegisterConnectivityChangedCallback(m_connectionChangedCallback);
                
            }
            
            NetworkCapabilities::~NetworkCapabilities()
            {
                m_connectivityService.UnregisterConnectivityChangedCallback(m_connectionChangedCallback);
            }
            
            bool NetworkCapabilities::StreamOverWifiOnly() const
            {
                return m_streamOverWifiOnly;
            }
            
            bool NetworkCapabilities::ConnectedToWifi() const
            {
                return m_connectedToWifi;
            }
            
            bool NetworkCapabilities::NetworkAvailable() const
            {
                return m_networkAvailable;
            }
            
            void NetworkCapabilities::SetStreamOverWifiOnlyMode(bool streamOverWifiOnlyEnabled)
            {
                const bool changed = streamOverWifiOnlyEnabled != m_streamOverWifiOnly;
                
                m_streamOverWifiOnly = streamOverWifiOnlyEnabled;
                m_persistentSettings.SetValue(NetworkCapabilities_OnlyStreamOverWifi_Key, m_streamOverWifiOnly);
                
                if (changed)
                {
                    m_notifyChangedCallbacks.ExecuteCallbacks();
                }
            }
            
            bool NetworkCapabilities::HttpCachingEnabled() const
            {
                return m_httpCache.GetEnabled();
            }
            
            void NetworkCapabilities::SetHttpCachingEnabled(bool httpCachingEnabled)
            {
                const bool changed = httpCachingEnabled != HttpCachingEnabled();
                
                m_httpCache.SetEnabled(httpCachingEnabled);
                m_persistentSettings.SetValue(NetworkCapabilities_HttpCacheEnabled_Key, httpCachingEnabled);
                
                if (changed)
                {
                    m_notifyChangedCallbacks.ExecuteCallbacks();
                }
            }
            
            void NetworkCapabilities::RegisterChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_notifyChangedCallbacks.AddCallback(callback);
            }
            
            void NetworkCapabilities::UnregisterChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_notifyChangedCallbacks.RemoveCallback(callback);
            }
            
            void NetworkCapabilities::HandleConnectionChanged(const bool &connected)
            {
                RefreshConnectivity();
            }
            
            void NetworkCapabilities::RefreshConnectivity()
            {
                const bool networkAvailable = QueryIsNetworkAvailable();
                const bool connectedToWifi = QueryIsConnectedToWifi();
                
                
                const bool changed = (networkAvailable != m_networkAvailable) || (connectedToWifi != m_connectedToWifi);
                m_networkAvailable = networkAvailable;
                m_connectedToWifi = connectedToWifi;
                
                if (changed)
                {
                    m_notifyChangedCallbacks.ExecuteCallbacks();
                }
            }
            
            bool NetworkCapabilities::QueryIsNetworkAvailable() const
            {
                return m_connectivityService.HasConnectivity();
            }
            
            bool NetworkCapabilities::QueryIsConnectedToWifi() const
            {
                return (m_connectivityService.GetConnectivityType() == Eegeo::Web::Wifi);
            }
        }
    }
}