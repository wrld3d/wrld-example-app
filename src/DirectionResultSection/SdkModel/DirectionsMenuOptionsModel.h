// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"
#include "Menu.h"
#include "MenuOptionsModel.h"



using namespace ExampleApp::Menu::View;

namespace ExampleApp
{
    namespace DirectionResultSection
    {
        namespace SdkModel
        {
            class DirectionsMenuOptionsModel : public MenuOptionsModel
            {
                
            public:
                DirectionsMenuOptionsModel(IMenuModel& menu);

                ~DirectionsMenuOptionsModel();

                void AddItem(const std::string& uniqueIdentifier,
                             const std::string& name,
                             const std::string& details,
                             const std::string& icon,
                             const std::string& duration,
                             Menu::View::IMenuOption* pOption);

            };
        }
    }
}
