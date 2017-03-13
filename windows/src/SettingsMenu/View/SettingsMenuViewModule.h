// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "WindowsNativeState.h"
#include "Types.h"
#include "Menu.h"
#include "MenuViewIncludes.h"
#include "ISettingsMenuViewModule.h"
#include "Search.h"
#include "BidirectionalBus.h"
#include "DesktopSettingsMenuController.h"
#include "Modality.h"
#include "IMenuViewModule.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            class SettingsMenuViewModule: public Menu::View::IMenuViewModule, private Eegeo::NonCopyable
            {
            private:
                SettingsMenuView* m_pView;
                DesktopSettingsMenuController* m_pController;

            public:
                SettingsMenuViewModule(
                    const std::string& viewName,
                    WindowsNativeState& nativeState,
                    Menu::View::IMenuModel& menuModelModel,
                    Menu::View::IMenuViewModel& menuViewModel,
                    Modality::View::IModalBackgroundView& modealBackgroundView,
                    Menu::View::IMenuView& searchMenuView,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    bool isInKioskMode
                );

                ~SettingsMenuViewModule();

                Menu::View::MenuController& GetMenuController();
                Menu::View::IMenuView& GetMenuView();
            };
        }
    }
}
