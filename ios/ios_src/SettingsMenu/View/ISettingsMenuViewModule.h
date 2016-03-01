// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"
#include "SettingsMenuViewIncludes.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            class ISettingsMenuViewModule
            {
            public:
                virtual ~ISettingsMenuViewModule() { }

                virtual Menu::View::MenuController& GetMenuController() const = 0;

                virtual SettingsMenuView& GetSettingsMenuView() const = 0;
            };
        }
    }
}
