// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"
#include "SearchMenuViewIncludes.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class ISearchMenuViewModule
            {
            public:
                virtual ~ISearchMenuViewModule() { }

                virtual Menu::View::MenuController& GetMenuController() const = 0;

                virtual SearchMenuView& GetSearchMenuView() const = 0;
            };
        }
    }
}
