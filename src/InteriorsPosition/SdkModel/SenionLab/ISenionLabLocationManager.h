// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include <map>
#include <string>

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                class ISenionLabLocationManager
                {
                public:
                    virtual void StartUpdatingLocation(const std::string& apiKey,
                                                       const std::string& apiSecret,
                                                       const std::map<int, std::string>& floorMap) = 0;
                    virtual void StopUpdatingLocation() = 0;
                };
            }
        }
    }
}
