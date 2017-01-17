// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageSenionSettingsTypeMessage.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        AboutPageSenionSettingsTypeMessage::AboutPageSenionSettingsTypeMessage(std::string apiKey, std::string apiSecret, std::map<int, std::string> floorMap, std::string interiorId)
        : m_senionApiKey(apiKey)
        , m_senionApiSecret(apiSecret)
        , m_senionfloorMap(floorMap)
        , m_senionInteriorId(interiorId)
        {
        }
        
        std::string AboutPageSenionSettingsTypeMessage::GetSenionApiKey() const
        {
            return m_senionApiKey;
        }
        
        std::string AboutPageSenionSettingsTypeMessage::GetSenionApiSecret() const
        {
            return m_senionApiSecret;
        }
        
        std::map<int, std::string> AboutPageSenionSettingsTypeMessage::GetSenionFloorMap() const
        {
            return m_senionfloorMap;
        }
        
        std::string AboutPageSenionSettingsTypeMessage::GetSenionInteriorId() const
        {
            return m_senionInteriorId;
        }
    }
}
