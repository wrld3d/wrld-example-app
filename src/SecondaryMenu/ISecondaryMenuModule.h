// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Menu.h"

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        class ISecondaryMenuModule
        {
        public:
            virtual ~ISecondaryMenuModule() { }
            
            virtual void AddMenuSection(const std::string& name, const std::string& icon, Menu::IMenuModel& menuModel, bool isExpandable) = 0;
            
            virtual Menu::IMenuModel& GetSecondaryMenuModel() const = 0;
            
            virtual Menu::IMenuOptionsModel& GetSecondaryMenuOptionsModel() const = 0;
            
            virtual Menu::IMenuViewModel& GetSecondaryMenuViewModel() const = 0;
        };
    }
}
