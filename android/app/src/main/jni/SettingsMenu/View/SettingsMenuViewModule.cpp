// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AndroidNativeState.h"
#include "Menu.h"
#include "SettingsMenuViewModule.h"
#include "SettingsMenuController.h"
#include "SettingsMenuView.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            SettingsMenuViewModule::SettingsMenuViewModule(
                const std::string& viewName,
                AndroidNativeState& nativeState,
                Menu::View::IMenuModel& menuModel,
                Menu::View::IMenuViewModel& menuViewModel,
				Modality::View::IModalBackgroundView& modalBackgroundView,
                ExampleAppMessaging::TMessageBus& messageBus
            )
            {
                ASSERT_UI_THREAD

                SettingsMenuView* view = Eegeo_NEW(SettingsMenuView)(nativeState, viewName);
                m_pView = view;

                m_pController = Eegeo_NEW(SettingsMenuController)(
                                    *view,
                                    menuModel,
                                    menuViewModel,
									modalBackgroundView,
                                    messageBus
                                );
            }

            SettingsMenuViewModule::~SettingsMenuViewModule()
            {
                ASSERT_UI_THREAD

                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pView;
            }

            Menu::View::MenuController& SettingsMenuViewModule::GetMenuController() const
            {
                ASSERT_UI_THREAD

                return *m_pController;
            }

            Menu::View::IMenuView& SettingsMenuViewModule::GetMenuView() const
            {
                ASSERT_UI_THREAD
                return *m_pView;
            }
        }
    }
}
