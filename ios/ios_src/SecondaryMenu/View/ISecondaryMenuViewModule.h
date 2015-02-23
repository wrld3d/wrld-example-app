// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SecondaryMenuViewIncludes.h"
#include "Menu.h"

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        namespace View
        {
            class ISecondaryMenuViewModule
            {
            public:
                virtual ~ISecondaryMenuViewModule() { }

                virtual Menu::View::MenuController& GetMenuController() const = 0;

                virtual SecondaryMenuView& GetSecondaryMenuView() const = 0;
            };
        }
    }
}
