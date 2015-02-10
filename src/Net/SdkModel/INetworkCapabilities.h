// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Net
    {
        namespace SdkModel
        {
            class INetworkCapabilities
            {
            public:
                virtual ~INetworkCapabilities() { }
                
                virtual bool StreamOverWifiOnly() const = 0;
                
                virtual bool ConnectedToWifi() const = 0;
                
                virtual bool NetworkAvailable() const = 0;
                
                virtual void SetStreamOverWifiOnlyMode(bool streamOverWifiOnlyEnabled) = 0;
                
                virtual bool HttpCachingEnabled() const = 0;
                
                virtual void SetHttpCachingEnabled(bool httpCachingEnabled) = 0;
            };
        }
    }
}
