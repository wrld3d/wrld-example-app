// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"
#include "PlaceJumps.h"

namespace ExampleApp
{
    namespace PlaceJumps
    {
        namespace SdkModel
        {
            class IPlaceJumpsModule
            {
            public:
                virtual ~IPlaceJumpsModule() { }

                virtual Menu::View::IMenuModel& GetPlaceJumpsMenuModel() const = 0;
                virtual IPlaceJumpController& GetPlaceJumpController() const = 0;
            };
        }
    }
}
