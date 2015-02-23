// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "AndroidNativeState.h"
#include "Types.h"
#include "Menu.h"
#include "PrimaryMenu.h"
#include "MenuViewIncludes.h"
#include "IMenuViewModule.h"
#include "Search.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        namespace View
        {
            class SecondaryMenuViewModule: public Menu::View::IMenuViewModule, private Eegeo::NonCopyable
            {
            private:
                Menu::View::MenuView* m_pView;
                Menu::View::MenuController* m_pController;

            public:
                SecondaryMenuViewModule(
                    const std::string& viewName,
                    AndroidNativeState& nativeState,
                    Menu::View::IMenuModel& menuModelModel,
                    Menu::View::IMenuViewModel& menuViewModel,
                    ExampleAppMessaging::TMessageBus& messageBus
                );

                ~SecondaryMenuViewModule();

                Menu::View::MenuController& GetMenuController() const;
                Menu::View::IMenuView& GetMenuView() const;
            };
        }
    }
}
