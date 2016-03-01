// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuController.h"

#include <string>

#include "BidirectionalBus.h"
#include "ICallback.h"
#include "ISettingsMenuView.h"
#include "Menu.h"
#include "Modality.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            class SettingsMenuController : public Menu::View::MenuController
            {
            private:
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Modality::View::IModalBackgroundView& m_modalBackgroundView;
                
                Eegeo::Helpers::TCallback1<SettingsMenuController, const AppModes::AppModeChangedMessage&> m_appModeChangedCallback;
                Eegeo::Helpers::TCallback0<SettingsMenuController> m_onModalBackgroundTappedCallback;
                
                void OnAppModeChanged(const AppModes::AppModeChangedMessage& message);
                
                bool TryDrag();
                
                void OnViewClicked();
                
                void OnModalBackgroundTapped();
            public:
                SettingsMenuController(Menu::View::IMenuView& menuView,
                                       Menu::View::IMenuModel& menuModel,
                                       Menu::View::IMenuViewModel& menuViewModel,
                                       Modality::View::IModalBackgroundView& modalBackgroundView,
                                       ExampleAppMessaging::TMessageBus& messageBus);

                ~SettingsMenuController();
            };
        }
    }
}
