// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Menu.h"
#include "SearchResultMenu.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        class ISearchResultMenuModule
        {
        public:
            virtual ~ISearchResultMenuModule() { }
            
            virtual Menu::IMenuOptionsModel& GetSearchResultMenuOptionsModel() const = 0;

            virtual Menu::IMenuModel& GetSearchResultMenuModel() const = 0;
            
            virtual Menu::IMenuViewModel& GetMenuViewModel() const = 0;
            
            virtual ISearchResultMenuViewModel& GetSearchResultMenuViewModel() const = 0;
        };
    }
}
