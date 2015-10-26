// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"
#include "PlaceJumps.h"
#include "GlobeCamera.h"

namespace ExampleApp
{
    namespace PlaceJumps
    {
        namespace SdkModel
        {
            class IPlaceJumpController
            {
            public:
                virtual ~IPlaceJumpController() { }

                virtual void JumpTo(const View::IPlaceJumpModel& jumpModel) = 0;
            };
        }
    }
}
