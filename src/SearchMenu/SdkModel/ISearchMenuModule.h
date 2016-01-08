// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

#include "Menu.h"
#include "SearchMenu.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace SdkModel
        {
            class ISearchMenuModule
            {
            public:
                virtual ~ISearchMenuModule() { }
                
                virtual void SetSearchSection(const std::string& name,
                                              Menu::View::IMenuModel& menuModel) = 0;
                
                virtual void AddMenuSection(const std::string& name,
                                            Menu::View::IMenuModel& menuModel,
                                            bool isExpandable) = 0;
                
                virtual Menu::View::IMenuModel& GetSearchMenuModel() const = 0;
                
                virtual Menu::View::IMenuOptionsModel& GetSearchMenuOptionsModel() const = 0;
                
                virtual Menu::View::IMenuViewModel& GetSearchMenuViewModel() const = 0;
                
                virtual Menu::View::IMenuSectionViewModel& GetSearchSectionViewModel() const = 0;
            };
        }
    }
}
