// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WorldPins.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            class IWorldPinOnMapViewModule
            {
            public:
                virtual ~IWorldPinOnMapViewModule() { }

                virtual WorldPinOnMapController& GetWorldPinOnMapController() const = 0;
            };
        }
    }
}
