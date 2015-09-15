// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "InteriorId.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            struct WorldPinInteriorData
            {
                WorldPinInteriorData(const Eegeo::Resources::Interiors::InteriorId& building = Eegeo::Resources::Interiors::InteriorId::NullId(),
                                     int floor = 0,
                                     bool showInExterior = false)
                : building(building)
                , floor(floor)
                , showInExterior(showInExterior)
                {
                    
                }
                
                Eegeo::Resources::Interiors::InteriorId building;
                int floor;
                bool showInExterior;
            };
        }
    }
}
