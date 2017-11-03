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
                Menu::View::IMenuModel& m_weatherMenuModel;

                Modality::View::IModalBackgroundView& m_modalBackgroundView;
                
                Eegeo::Helpers::TCallback0<SettingsMenuController> m_onModalBackgroundTappedCallback;

                bool m_hideWeather;
                
                bool TryDrag();
                
                void OnViewClicked();
                
                void OnModalBackgroundTapped();

            protected:
                void OnAppModeChanged(const AppModes::AppModeChangedMessage &message);

                bool ShouldHideSection(ExampleApp::Menu::View::IMenuSectionViewModel& section);

            public:
                SettingsMenuController(Menu::View::IMenuView& menuView,
                                       Menu::View::IMenuModel& menuModel,
                                       Menu::View::IMenuViewModel& menuViewModel,
                                       Menu::View::IMenuModel& weatherMenuModel,
                                       Modality::View::IModalBackgroundView& modalBackgroundView,
                                       ExampleAppMessaging::TMessageBus& messageBus);

                ~SettingsMenuController();
            };
        }
    }
}
