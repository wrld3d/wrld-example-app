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
#include "SettingsMenuController.h"
#include "Modality.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            class SettingsMenuViewModule: public ISettingsMenuViewModule, private Eegeo::NonCopyable
            {
            private:
                SettingsMenuView* m_pView;
                SettingsMenuController* m_pController;

            public:
                SettingsMenuViewModule(
                    const std::string& viewName,
                    WindowsNativeState& nativeState,
                    Menu::View::IMenuModel& menuModelModel,
                    Menu::View::IMenuViewModel& menuViewModel,
                    Modality::View::IModalBackgroundView& modealBackgroundView,
                    ExampleAppMessaging::TMessageBus& messageBus
                );

                ~SettingsMenuViewModule();

                Menu::View::MenuController& GetMenuController() const;
                Menu::View::IMenuView& GetMenuView() const;
            };
        }
    }
}
