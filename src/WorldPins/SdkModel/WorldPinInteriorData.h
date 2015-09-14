// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            struct WorldPinInteriorData
            {
                WorldPinInteriorData(const std::string& building = "", int floor = 0, bool showInExterior = true)
                : building(building)
                , floor(floor)
                , showInExterior(showInExterior)
                {
                    
                }
                
                std::string building;
                int floor;
                bool showInExterior;
            };
        }
    }
}
