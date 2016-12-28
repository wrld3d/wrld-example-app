// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once
#include <map>
#include <string>


namespace ExampleApp
{
    namespace InteriorsPosition
    {
        class InteriorsPositionStartUpdatingLocationMessage
        {
        public:
            InteriorsPositionStartUpdatingLocationMessage(std::string apiKey,
                                                    std::string apiSecret,
                                                    std::map<int, std::string> floorMap,
                                                    int currentFloorIndex)
            : m_apiKey(apiKey)
            , m_apiSecret(apiSecret)
            , m_floorMap(floorMap)
            , m_currentFloorIndex(currentFloorIndex)
            {
            }
            
            std::string GetApiKey() const { return m_apiKey; }
            std::string GetApiSecret() const { return m_apiSecret; }
            std::map<int, std::string> GetFloorMap() const { return m_floorMap; }
            int GetCurrentFloorIndex() const { return m_currentFloorIndex; }
            
        private:
            std::string m_apiKey;
            std::string m_apiSecret;
            std::map<int, std::string> m_floorMap;
            int m_currentFloorIndex;
        };
    }
}
