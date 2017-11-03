// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace SdkModel
        {
            class ISettingsMenuModule
            {
            public:
                virtual ~ISettingsMenuModule() { }

                virtual void AddMenuSection(const std::string& name,
                                            Menu::View::IMenuModel& menuModel,
                                            bool isExpandable) = 0;
                
                virtual Menu::View::IMenuModel& GetSettingsMenuModel() const = 0;

                virtual Menu::View::IMenuOptionsModel& GetSettingsMenuOptionsModel() const = 0;

                virtual Menu::View::IMenuViewModel& GetSettingsMenuViewModel() const = 0;

                enum class MenuModelTypes
                {
                    Weather,
                    Options,
                    About
                };

                virtual Menu::View::IMenuModel& GetMenuModel(MenuModelTypes model) const = 0;
            };
        }
    }
}
