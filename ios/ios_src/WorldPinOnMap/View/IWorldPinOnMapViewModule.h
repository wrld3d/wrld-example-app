// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WorldPinOnMapViewIncludes.h"
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

                virtual WorldPinOnMapViewContainer& GetWorldPinOnMapView() const = 0;
            };
        }
    }
}
