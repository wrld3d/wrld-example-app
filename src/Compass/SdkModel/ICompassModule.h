// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Compass.h"
#include "ScreenControlViewModelIncludes.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            class ICompassModule
            {
            public:
                virtual ~ICompassModule() { }

                virtual ICompassModel& GetCompassModel() const = 0;

                virtual View::ICompassViewModel& GetCompassViewModel() const = 0;

                virtual ICompassUpdateController& GetCompassUpdateController() const = 0;

                virtual ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel() const = 0;

                virtual ICompassTouchController& GetTouchController() = 0;
            };
        }
    }
}
