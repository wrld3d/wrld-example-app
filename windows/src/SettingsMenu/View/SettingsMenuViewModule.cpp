// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WindowsNativeState.h"
#include "Menu.h"
#include "SettingsMenuViewModule.h"
#include "SettingsMenuController.h"
#include "SettingsMenuView.h"
#include "WindowsAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            SettingsMenuViewModule::SettingsMenuViewModule(
                const std::string& viewName,
                WindowsNativeState& nativeState,
                Menu::View::IMenuModel& menuModel,
                Menu::View::IMenuViewModel& menuViewModel,
                Modality::View::IModalBackgroundView& modealBackgroundView,
                Menu::View::IMenuView& searchMenuView,
                ExampleAppMessaging::TMessageBus& messageBus,
                bool isInKioskMode
            )
            {
                m_pView = Eegeo_NEW(SettingsMenuView)(nativeState, viewName, isInKioskMode);

                m_pController = Eegeo_NEW(DesktopSettingsMenuController)(
                                    *m_pView,
                                    menuModel,
                                    menuViewModel,
                                    modealBackgroundView,
                                    searchMenuView,
                                    messageBus
                                );
            }

            SettingsMenuViewModule::~SettingsMenuViewModule()
            {
                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pView;
            }

            Menu::View::MenuController& SettingsMenuViewModule::GetMenuController()
            {
                return *m_pController;
            }

            Menu::View::IMenuView& SettingsMenuViewModule::GetMenuView()
            {
                return *m_pView;
            }
        }
    }
}
