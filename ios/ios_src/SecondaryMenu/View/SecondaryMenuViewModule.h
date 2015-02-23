// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Menu.h"
#include "ISecondaryMenuViewModule.h"
#include "Rendering.h"
#include "Modality.h"
#include "Search.h"
#include "BidirectionalBus.h"
#include "SecondaryMenuController.h"
#include "CustomTableDataProvider.h"

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        namespace View
        {
            class SecondaryMenuViewModule: public ISecondaryMenuViewModule, private Eegeo::NonCopyable
            {
            private:
                SecondaryMenuController* m_pController;
                SecondaryMenuView* m_pView;
                CustomTableDataProvider* m_pDataProvider;

            public:
                SecondaryMenuViewModule(Menu::View::IMenuModel& secondaryMenuModel,
                                        Menu::View::IMenuViewModel& secondaryMenuViewModel,
                                        const Eegeo::Rendering::ScreenProperties& screenProperties,
                                        ExampleAppMessaging::TMessageBus& messageBus);

                ~SecondaryMenuViewModule();

                Menu::View::MenuController& GetMenuController() const;

                SecondaryMenuView& GetSecondaryMenuView() const;
            };
        }
    }
}
