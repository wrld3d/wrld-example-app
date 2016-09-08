// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"
#include "DirectionsMenuViewIncludes.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace View
        {
            class IDirectionsMenuViewModule
            {
            public:
                virtual ~IDirectionsMenuViewModule() { }

                virtual Menu::View::MenuController& GetMenuController() const = 0;

                virtual DirectionsMenuView& GetDirectionsMenuView() const = 0;
            };
        }
    }
}
