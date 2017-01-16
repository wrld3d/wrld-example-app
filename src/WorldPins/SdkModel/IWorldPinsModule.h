// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WorldPins.h"
#include "IScreenControlViewModel.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class IWorldPinsModule
            {
            public:
                virtual ~IWorldPinsModule() { }
                
                virtual void Update(float dt) = 0;

                virtual IWorldPinsService& GetWorldPinsService() const = 0;

                virtual IWorldPinsFactory& GetWorldPinsFactory() const = 0;

                virtual IWorldPinsVisibilityController& GetWorldPinsVisibilityController() const = 0;
            };
        }
    }
}
