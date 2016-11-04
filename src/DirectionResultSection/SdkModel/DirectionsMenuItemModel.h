// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "IMenuOption.h"
#include "MenuItemModel.h"


using namespace ExampleApp::Menu::View;

namespace ExampleApp
{
    namespace DirectionResultSection
    {
        namespace SdkModel
        {
            class DirectionsMenuItemModel:public MenuItemModel
            {
            private:
                std::string m_routeDuration;

            public:
                DirectionsMenuItemModel(const std::string& identifier,
                                        const std::string& name,
                                        const std::string& details,
                                        const std::string& icon,                                                   const std::string& duration,
                                        IMenuOption* pOption);

                ~DirectionsMenuItemModel();

                std::string SerializeJson() const;
                
                const std::string& Duration() const;
            };
        }
    }
}
