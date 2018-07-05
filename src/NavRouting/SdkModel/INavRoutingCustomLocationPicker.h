// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "NavRouting.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class INavRoutingCustomLocationPicker {
            public:

                virtual ~INavRoutingCustomLocationPicker() {}

                virtual void StartSearching(bool forStartLocation) = 0;

                virtual void StopSearching() = 0;

                virtual bool HandleTouchTap(float screenX, float screenY) = 0;
            };
        }
    }
}