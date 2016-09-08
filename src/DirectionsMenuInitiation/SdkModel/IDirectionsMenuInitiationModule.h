// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "DirectionsMenuInitiation.h"
#include "Camera.h"
#include "ScreenControlViewModelIncludes.h"

namespace ExampleApp
{
    namespace DirectionsMenuInitiation
    {
        namespace SdkModel
        {
            class IDirectionsMenuInitiationModule
            {
            public:
                virtual ~IDirectionsMenuInitiationModule() {}

                virtual View::IDirectionsMenuInitiationViewModel& GetDirectionsMenuInitiationViewModel() const = 0;

                virtual ScreenControl::View::IScreenControlViewModel& GetInitiationScreenControlViewModel() const = 0;
            };
        }
    }
}
