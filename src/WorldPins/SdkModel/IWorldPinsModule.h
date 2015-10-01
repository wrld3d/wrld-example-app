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

                virtual IWorldPinsService& GetWorldPinsService() const = 0;

                virtual IWorldPinsFactory& GetWorldPinsFactory() const = 0;

                virtual IWorldPinsScaleController& GetWorldPinsScaleController() const = 0;
                
                virtual IWorldPinsFloorHeightController& GetWorldPinsFloorHeightController() const = 0;

                virtual View::IWorldPinInFocusViewModel& GetWorldPinInFocusViewModel() const = 0;

                virtual IWorldPinsInFocusController& GetWorldPinsInFocusController() const = 0;

                virtual ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel() const = 0;
            };
        }
    }
}
