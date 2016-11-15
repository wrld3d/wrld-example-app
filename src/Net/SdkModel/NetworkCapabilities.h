// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "INetworkCapabilities.h"
#include "IConnectivityService.h"
#include "IHttpCache.h"
#include "PersistentSettings.h"
#include "CallbackCollection.h"


namespace ExampleApp
{
    namespace Net
    {
        namespace SdkModel
        {
            class NetworkCapabilities : public INetworkCapabilities, private Eegeo::NonCopyable
            {
                Eegeo::Web::IConnectivityService& m_connectivityService;
                Eegeo::Helpers::IHttpCache& m_httpCache;
                PersistentSettings::IPersistentSettingsModel& m_persistentSettings;
                bool m_streamOverWifiOnly;
                bool m_networkAvailable;
                bool m_connectedToWifi;
                
                Eegeo::Helpers::TCallback1<NetworkCapabilities, const bool&> m_connectionChangedCallback;
                Eegeo::Helpers::CallbackCollection0 m_notifyChangedCallbacks;
                
                void RefreshConnectivity();
                bool QueryIsNetworkAvailable() const;
                bool QueryIsConnectedToWifi() const;
            public:
                NetworkCapabilities(Eegeo::Web::IConnectivityService& connectivityService,
                                    Eegeo::Helpers::IHttpCache& httpCache,
                                    PersistentSettings::IPersistentSettingsModel& persistentSettings);
                
                ~NetworkCapabilities();
                
                bool StreamOverWifiOnly() const;
                
                bool ConnectedToWifi() const;
                
                bool NetworkAvailable() const;
                
                bool HttpCachingEnabled() const;
                
                void SetStreamOverWifiOnlyMode(bool streamOverWifiOnlyEnabled);
                
                void SetHttpCachingEnabled(bool httpCachingEnabled);
                
                void RegisterChangedCallback(Eegeo::Helpers::ICallback0& callback);
                void UnregisterChangedCallback(Eegeo::Helpers::ICallback0& callback);
                
                void HandleConnectionChanged(const bool &connected);
            };
        }
    }
}