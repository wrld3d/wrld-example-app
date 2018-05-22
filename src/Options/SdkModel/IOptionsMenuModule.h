// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace SdkModel
        {
            class IOptionsMenuModule
            {
            public:
                virtual ~IOptionsMenuModule() { }

                virtual Menu::View::IMenuModel& GetOptionsMenuModel() const = 0;
            };
        }
    }
}
