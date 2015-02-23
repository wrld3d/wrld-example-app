// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "PrimaryMenuViewIncludes.h"
#include "Menu.h"

namespace ExampleApp
{
    namespace PrimaryMenu
    {
        namespace View
        {
            class IPrimaryMenuViewModule
            {
            public:
                virtual ~IPrimaryMenuViewModule() { }

                virtual Menu::View::MenuController& GetMenuController() const = 0;

                virtual PrimaryMenuView& GetPrimaryMenuView() const = 0;
            };
        }
    }
}
