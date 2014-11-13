// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Menu.h"
#include <string>

namespace ExampleApp
{
    namespace PrimaryMenu
    {
        class IPrimaryMenuModule
        {
        public:
            virtual ~IPrimaryMenuModule() { }
            
            virtual Menu::IMenuModel& GetPrimaryMenuModel() const = 0;
            
            virtual void AddMenuSection(const std::string& name, const std::string& icon, Menu::IMenuModel& menuModel, bool isExpandable) = 0;
            
            virtual Menu::IMenuOptionsModel& GetPrimaryMenuOptionsModel() const = 0;
            
            virtual Menu::IMenuViewModel& GetPrimaryMenuViewModel() const = 0;
        };
    }
}
