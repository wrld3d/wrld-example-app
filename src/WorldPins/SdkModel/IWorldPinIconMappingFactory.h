// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WorldPins.h"
#include "Types.h"

#include <vector>
#include <string>

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class IWorldPinIconMappingFactory
            {
            public:
                virtual ~IWorldPinIconMappingFactory() { }
                
                virtual IWorldPinIconMapping* Create() const = 0;
                
            };
        }
    }
}