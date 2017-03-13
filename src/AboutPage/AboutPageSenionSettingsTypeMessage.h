// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <map>

namespace ExampleApp
{
    namespace AboutPage
    {
        class AboutPageSenionSettingsTypeMessage
        {
            std::string m_senionApiKey;
            std::string m_senionApiSecret;
            std::map<int, std::string> m_senionfloorMap;
            std::string m_senionInteriorId;
            
        public:
            AboutPageSenionSettingsTypeMessage(std::string apiKey, std::string apiSecret, std::map<int, std::string> floorMap, std::string m_senionInteriorId);
            
            std::string GetSenionApiKey() const;
            std::string GetSenionApiSecret() const;
            std::map<int, std::string> GetSenionFloorMap() const;
            std::string GetSenionInteriorId() const;
        };
    }
}
