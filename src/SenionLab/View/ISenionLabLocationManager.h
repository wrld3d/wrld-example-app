// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include <map>
#include <string>

namespace ExampleApp
{
    namespace SenionLab
    {
        namespace View
        {
            class ISenionLabLocationManager
            {
            public:
                virtual void StartUpdatingLocation(std::string apiKey,
                								   std::string apiSecret,
												   std::map<int, std::string> floorMap) = 0;

                virtual ~ISenionLabLocationManager(){}
                virtual void StopUpdatingLocation() = 0;
            };
        }
    }
}
