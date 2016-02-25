// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WindowsNativeState.h"
#include "Menu.h"
#include "MenuViewModule.h"
#include "MenuController.h"
#include "MenuView.h"
#include "WindowsAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            MenuViewModule::MenuViewModule(
                const std::string& viewName,
                WindowsNativeState& nativeState,
                IMenuModel& menuModel,
                IMenuViewModel& menuViewModel,
                ExampleAppMessaging::TMessageBus& messageBus
            )
            {
                ASSERT_UI_THREAD

               /* m_pView = Eegeo_NEW(MenuView)(nativeState, viewName);
                m_pController = Eegeo_NEW(MenuController)(menuModel, menuViewModel, *m_pView, messageBus);*/
            }

            MenuViewModule::~MenuViewModule()
            {
                ASSERT_UI_THREAD

                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pView;
            }

            MenuController& MenuViewModule::GetMenuController() const
            {
                ASSERT_UI_THREAD

                return *m_pController;
            }

            IMenuView& MenuViewModule::GetMenuView() const
            {
                ASSERT_UI_THREAD

                return *m_pView;
            }
        }
    }
}
