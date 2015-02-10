// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "INetworkCapabilities.h"
#include "IConnectivityService.h"
#include "IHttpCache.h"
#include "PersistentSettings.h"

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
                
            public:
                NetworkCapabilities(Eegeo::Web::IConnectivityService& connectivityService,
                                    Eegeo::Helpers::IHttpCache& httpCache,
                                    PersistentSettings::IPersistentSettingsModel& persistentSettings);
                
                bool StreamOverWifiOnly() const;
                
                bool ConnectedToWifi() const;
                
                bool NetworkAvailable() const;
                
                bool HttpCachingEnabled() const;
                
                void SetStreamOverWifiOnlyMode(bool streamOverWifiOnlyEnabled);
                
                void SetHttpCachingEnabled(bool httpCachingEnabled);
            };
        }
    }
}
