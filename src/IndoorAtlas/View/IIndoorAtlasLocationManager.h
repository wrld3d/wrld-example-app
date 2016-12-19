// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include <map>
#include <string>

namespace ExampleApp
{
    namespace IndoorAtlas
    {
        namespace View
        {
            class IIndoorAtlasLocationManager
            {
            public:
                virtual void StartUpdatingLocation(std::string apiKey,
                								   std::string apiSecret,
												   std::map<int, std::string> floorMap,
												   int floorIndex) = 0;

                virtual ~IIndoorAtlasLocationManager(){}
                virtual void StopUpdatingLocation() = 0;
                virtual void SetFloorIndex(int floorIndex) = 0;
            };
        }
    }
}
