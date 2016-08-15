// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "INetworkCapabilities.h"
#include "IConnectivityService.h"
#include "IHttpCache.h"
#include "PersistentSettings.h"
#include "CallbackCollection.h"
#include <memory>

namespace ExampleApp
{
    namespace Net
    {
        namespace SdkModel
        {
            class NetworkCapabilities : public INetworkCapabilities, private Eegeo::NonCopyable
            {
                const std::shared_ptr<Eegeo::Web::IConnectivityService> m_connectivityService;
                const std::shared_ptr<Eegeo::Helpers::IHttpCache> m_httpCache;
                const std::shared_ptr<PersistentSettings::IPersistentSettingsModel> m_persistentSettings;
                bool m_streamOverWifiOnly;
                bool m_networkAvailable;
                bool m_connectedToWifi;
                
                Eegeo::Helpers::TCallback1<NetworkCapabilities, const bool&> m_connectionChangedCallback;
                Eegeo::Helpers::CallbackCollection0 m_notifyChangedCallbacks;
                
                void RefreshConnectivity();
                bool QueryIsNetworkAvailable() const;
                bool QueryIsConnectedToWifi() const;
            public:
                NetworkCapabilities(const std::shared_ptr<Eegeo::Web::IConnectivityService>& connectivityService,
                                    const std::shared_ptr<Eegeo::Helpers::IHttpCache>& httpCache,
                                    const std::shared_ptr<PersistentSettings::IPersistentSettingsModel>& persistentSettings);
                
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