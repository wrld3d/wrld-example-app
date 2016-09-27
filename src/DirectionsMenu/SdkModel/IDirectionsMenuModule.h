// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

#include "Menu.h"
#include "DirectionsMenu.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace SdkModel
        {
            class IDirectionsMenuModule
            {
            public:
                virtual ~IDirectionsMenuModule() { }
                
                virtual void SetSearchSection(const std::string& name,
                                              Menu::View::IMenuModel& menuModel) = 0;
                
//                virtual void AddMenuSection(const std::string& name,
//                                            Menu::View::IMenuModel& menuModel,
//                                            bool isExpandable) = 0;
//                
                virtual Menu::View::IMenuModel& GetDirectionsMenuModel() const = 0;
                
                virtual Menu::View::IMenuViewModel& GetDirectionsMenuViewModel() const = 0;
                virtual Menu::View::IMenuSectionViewModel& GetSearchSectionViewModel() const = 0;
            };
        }
    }
}
