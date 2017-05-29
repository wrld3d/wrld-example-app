// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <map>

namespace ExampleApp
{
    namespace AboutPage
    {
        class AboutPageIndoorPositionSettingsMessage
        {
            std::string m_apiKey;
            std::string m_apiSecret;
            std::map<int, std::string> m_floorMap;
            std::string m_interiorId;
            
        public:
            AboutPageIndoorPositionSettingsMessage(std::string apiKey, std::string apiSecret, std::map<int, std::string> floorMap, std::string interiorId);
            
            std::string GetApiKey() const;
            std::string GetApiSecret() const;
            std::map<int, std::string> GetFloorMap() const;
            std::string GetInteriorId() const;
        };
    }
}
