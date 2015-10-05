// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Camera.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class IWorldPinsFloorHeightController
            {
            public:
                virtual ~IWorldPinsFloorHeightController() { }
                
                virtual void Update(float deltaSeconds) = 0;
            };
        }
    }
}
