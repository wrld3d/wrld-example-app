// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"
#include <string>

namespace ExampleApp
{
    namespace PrimaryMenu
    {
        namespace View
        {
            class IPrimaryMenuModule
            {
            public:
                virtual ~IPrimaryMenuModule() { }

                virtual Menu::View::IMenuModel& GetPrimaryMenuModel() const = 0;

                virtual void AddMenuSection(const std::string& name, const std::string& icon, Menu::View::IMenuModel& menuModel, bool isExpandable) = 0;

                virtual Menu::View::IMenuOptionsModel& GetPrimaryMenuOptionsModel() const = 0;

                virtual Menu::View::IMenuViewModel& GetPrimaryMenuViewModel() const = 0;
            };
        }
    }
}
