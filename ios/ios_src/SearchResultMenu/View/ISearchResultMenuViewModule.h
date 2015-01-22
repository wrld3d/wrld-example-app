// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchResultMenuViewIncludes.h"
#include "Menu.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            class ISearchResultMenuViewModule
            {
            public:
                virtual ~ISearchResultMenuViewModule() { }

                virtual Menu::View::MenuController& GetMenuController() const = 0;

                virtual SearchResultMenuView& GetSearchResultMenuView() const = 0;
            };
        }
    }
}
