// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WindowsNativeState.h"
#include "Menu.h"
#include "SecondaryMenuViewModule.h"
//#include "SecondaryMenuController.h"
#include "SecondaryMenuView.h"
#include "WindowsAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        namespace View
        {
            SecondaryMenuViewModule::SecondaryMenuViewModule(
                const std::string& viewName,
                WindowsNativeState& nativeState,
                Menu::View::IMenuModel& menuModel,
                Menu::View::IMenuViewModel& menuViewModel,
                ExampleAppMessaging::TMessageBus& messageBus
            )
            {
                ASSERT_UI_THREAD

                /*SecondaryMenuView* view = Eegeo_NEW(SecondaryMenuView)(nativeState, viewName);
                m_pView = view;

                m_pController = Eegeo_NEW(SecondaryMenuController)(
                                    *view,
                                    *view,
                                    menuModel,
                                    menuViewModel,
                                    messageBus
                                );*/
            }

            SecondaryMenuViewModule::~SecondaryMenuViewModule()
            {
                ASSERT_UI_THREAD

                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pView;
            }

            Menu::View::MenuController& SecondaryMenuViewModule::GetMenuController() const
            {
                ASSERT_UI_THREAD

                return *m_pController;
            }

            Menu::View::IMenuView& SecondaryMenuViewModule::GetMenuView() const
            {
                ASSERT_UI_THREAD
                return *m_pView;
            }
        }
    }
}
