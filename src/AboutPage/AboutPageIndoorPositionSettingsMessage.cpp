// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageIndoorPositionSettingsMessage.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        AboutPageIndoorPositionSettingsMessage::AboutPageIndoorPositionSettingsMessage(std::string apiKey, std::string apiSecret, std::map<int, std::string> floorMap, std::string interiorId)
        : m_apiKey(apiKey)
        , m_apiSecret(apiSecret)
        , m_floorMap(floorMap)
        , m_interiorId(interiorId)
        {
        }
        
        std::string AboutPageIndoorPositionSettingsMessage::GetApiKey() const
        {
            return m_apiKey;
        }
        
        std::string AboutPageIndoorPositionSettingsMessage::GetApiSecret() const
        {
            return m_apiSecret;
        }
        
        std::map<int, std::string> AboutPageIndoorPositionSettingsMessage::GetFloorMap() const
        {
            return m_floorMap;
        }
        
        std::string AboutPageIndoorPositionSettingsMessage::GetInteriorId() const
        {
            return m_interiorId;
        }
    }
}
