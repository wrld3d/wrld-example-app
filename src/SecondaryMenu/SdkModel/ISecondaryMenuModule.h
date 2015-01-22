// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        namespace SdkModel
        {
            class ISecondaryMenuModule
            {
            public:
                virtual ~ISecondaryMenuModule() { }

                virtual void AddMenuSection(const std::string& name, const std::string& icon, Menu::View::IMenuModel& menuModel, bool isExpandable) = 0;

                virtual Menu::View::IMenuModel& GetSecondaryMenuModel() const = 0;

                virtual Menu::View::IMenuOptionsModel& GetSecondaryMenuOptionsModel() const = 0;

                virtual Menu::View::IMenuViewModel& GetSecondaryMenuViewModel() const = 0;
            };
        }
    }
}
