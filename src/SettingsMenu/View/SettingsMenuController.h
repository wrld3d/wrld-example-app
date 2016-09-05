// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuController.h"

#include <string>

#include "BidirectionalBus.h"
#include "ICallback.h"
#include "ISettingsMenuView.h"
#include "Menu.h"
#include "Modality.h"
#include "SettingsMenu.h"

#include <memory>

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            class SettingsMenuController : public Menu::View::MenuController
            {
            private:
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                const std::shared_ptr<Modality::View::IModalBackgroundView> m_modalBackgroundView;
                
                Eegeo::Helpers::TCallback1<SettingsMenuController, const AppModes::AppModeChangedMessage&> m_appModeChangedCallback;
                Eegeo::Helpers::TCallback0<SettingsMenuController> m_onModalBackgroundTappedCallback;
                
                void OnAppModeChanged(const AppModes::AppModeChangedMessage& message);
                
                bool TryDrag();
                
                void OnViewClicked();
                
                void OnModalBackgroundTapped();
            public:
                SettingsMenuController(const std::shared_ptr<Menu::View::IMenuView>& menuView,
                                       const std::shared_ptr<SettingsMenuModel>& menuModel,
                                       const std::shared_ptr<SettingsMenuViewModel>& menuViewModel,
                                       const std::shared_ptr<Modality::View::IModalBackgroundView>& modalBackgroundView,
                                       const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);

                ~SettingsMenuController();
            };
        }
    }
}
