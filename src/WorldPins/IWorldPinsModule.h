// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "WorldPins.h"
#include "IScreenControlViewModel.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        class IWorldPinsModule
        {
        public:
            virtual ~IWorldPinsModule() { }
            
            virtual IWorldPinsService& GetWorldPinsService() const = 0;
            
            virtual IWorldPinsFactory& GetWorldPinsFactory() const = 0;
            
            virtual IWorldPinsScaleController& GetWorldPinsScaleController() const = 0;
            
            virtual IWorldPinInFocusViewModel& GetWorldPinInFocusViewModel() const = 0;

            virtual IWorldPinsInFocusController& GetWorldPinsInFocusController() const = 0;
            
            virtual ScreenControlViewModel::IScreenControlViewModel& GetScreenControlViewModel() const = 0;
        };
    }
}
