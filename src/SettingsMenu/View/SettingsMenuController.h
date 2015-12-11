// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuController.h"

#include <string>

#include "BidirectionalBus.h"
#include "ICallback.h"
#include "ISettingsMenuView.h"
#include "Menu.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            class SettingsMenuController : public Menu::View::MenuController
            {
            private:
                ExampleAppMessaging::TMessageBus& m_messageBus;
                bool m_appModeAllowsOpen;
                
                Eegeo::Helpers::TCallback1<SettingsMenuController, const AppModes::AppModeChangedMessage&> m_appModeChangedCallback;
                
                void OnAppModeChanged(const AppModes::AppModeChangedMessage& message);
                
                bool TryDrag();
                
                void OnViewClicked();
            public:
                SettingsMenuController(Menu::View::IMenuView& menuView,
                                       Menu::View::IMenuModel& menuModel,
                                       Menu::View::IMenuViewModel& menuViewModel,
                                       ExampleAppMessaging::TMessageBus& messageBus);

                ~SettingsMenuController();
            };
        }
    }
}
