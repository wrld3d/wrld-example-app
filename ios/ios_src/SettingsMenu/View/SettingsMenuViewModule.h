// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISettingsMenuViewModule.h"

#include "Types.h"
#include "Menu.h"
#include "Modality.h"
#include "Rendering.h"
#include "BidirectionalBus.h"
#include "SettingsTableDataProvider.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            class SettingsMenuViewModule: public ISettingsMenuViewModule, private Eegeo::NonCopyable
            {
            private:
                SettingsMenuController* m_pController;
                SettingsMenuView* m_pView;
                SettingsTableDataProvider* m_pDataProvider;

            public:
                SettingsMenuViewModule(Menu::View::IMenuModel& settingsMenuModel,
                                       Menu::View::IMenuViewModel& settingsMenuViewModel,
                                       const Eegeo::Rendering::ScreenProperties& screenProperties,
                                       Modality::View::IModalBackgroundView& modalBackgroundView,
                                       ExampleAppMessaging::TMessageBus& messageBus);

                ~SettingsMenuViewModule();

                Menu::View::MenuController& GetMenuController() const;

                SettingsMenuView& GetSettingsMenuView() const;
            };
        }
    }
}
