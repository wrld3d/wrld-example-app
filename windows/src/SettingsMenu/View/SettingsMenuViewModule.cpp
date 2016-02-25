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
                ExampleAppMessaging::TMessageBus& messageBus
            )
            {
                m_pView = Eegeo_NEW(SettingsMenuView)(nativeState, viewName);

                m_pController = Eegeo_NEW(SettingsMenuController)(
                                    *m_pView,
                                    menuModel,
                                    menuViewModel,
                                    modealBackgroundView,
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
