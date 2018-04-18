// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace SdkModel
        {
            class ISettingsMenuModule
            {
            public:
                virtual ~ISettingsMenuModule() { }

                virtual Menu::View::IMenuModel& GetOptionsMenuModel() const = 0;

                virtual Menu::View::IMenuModel& GetAboutMenuModel() const = 0;
            };
        }
    }
}
