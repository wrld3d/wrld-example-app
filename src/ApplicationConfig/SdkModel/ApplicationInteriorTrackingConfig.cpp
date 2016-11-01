// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "ApplicationInteriorTrackingInfo.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            ApplicationInteriorTrackingConfig::ApplicationInteriorTrackingConfig(const std::string& apiKey, const std::string& apiSecret)
            : m_apiKey(apiKey)
            , m_apiSecret(apiSecret)
            {
            }
            
            ApplicationInteriorTrackingConfig::~ApplicationInteriorTrackingConfig()
            {
            }
            
            const std::string& ApplicationInteriorTrackingConfig::GetApiKey() const
            {
                return m_apiKey;
            }
            
            const std::string& ApplicationInteriorTrackingConfig::GetApiSecret() const
            {
                return m_apiSecret;
            }
        }
    }
}
