// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuViewIncludes.h"
#include "Menu.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            class IMenuViewModule
            {
            public:
                virtual ~IMenuViewModule() { }

                virtual IMenuView& GetMenuView() const = 0;
                virtual MenuController& GetMenuController() const = 0;
            };
        }
    }
}
