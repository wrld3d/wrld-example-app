// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"
#include "SearchResultMenu.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace SdkModel
        {
            class ISearchResultMenuModule
            {
            public:
                virtual ~ISearchResultMenuModule() { }

                virtual Menu::View::IMenuOptionsModel& GetSearchResultMenuOptionsModel() const = 0;

                virtual Menu::View::IMenuModel& GetSearchResultMenuModel() const = 0;

                virtual Menu::View::IMenuViewModel& GetMenuViewModel() const = 0;

                virtual View::ISearchResultMenuViewModel& GetSearchResultMenuViewModel() const = 0;
            };
        }
    }
}
