// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            class ApplicationInteriorTrackingConfig
            {
            public:
                ApplicationInteriorTrackingConfig(const std::string& apiKey, const std::string& apiSecret);
                ~ApplicationInteriorTrackingConfig();
                
                const std::string& GetApiKey() const;
                const std::string& GetApiSecret() const;
                
            private:
                const std::string m_apiKey;
                const std::string m_apiSecret;
            };
        }
    }
}
