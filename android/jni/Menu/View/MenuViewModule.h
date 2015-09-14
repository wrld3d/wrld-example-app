// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "AndroidNativeState.h"
#include "Types.h"
#include "Menu.h"
#include "MenuViewIncludes.h"
#include "IMenuViewModule.h"
#include "MenuController.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            class MenuViewModule: public IMenuViewModule, private Eegeo::NonCopyable
            {
            private:
                MenuView* m_pView;
                MenuController* m_pController;

            public:
                MenuViewModule(
                    const std::string& viewName,
                    AndroidNativeState& nativeState,
                    IMenuModel& menuModelModel,
                    IMenuViewModel& menuViewModel,
                    ExampleAppMessaging::TMessageBus& messageBus
                );

                ~MenuViewModule();

                MenuController& GetMenuController() const;
                IMenuView& GetMenuView() const;
            };
        }
    }
}
