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
            class DesktopSettingsMenuController : public Menu::View::MenuController
            {
                enum Control
                {
                    SearchMenu = 0,
                    POICard,
                    Num
                };

            private:
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                const std::shared_ptr<Modality::View::IModalBackgroundView> m_modalBackgroundView;
                bool m_appModeAllowsOpen;
                bool m_isControlOpen[Control::Num];
                AppModes::SdkModel::AppMode m_currentAppMode;
                
                Eegeo::Helpers::TCallback1<DesktopSettingsMenuController, const AppModes::AppModeChangedMessage&> m_appModeChangedCallback;
                Eegeo::Helpers::TCallback0<DesktopSettingsMenuController> m_onModalBackgroundTappedCallback;

                const std::shared_ptr<Menu::View::IMenuView> m_searchMenuView;
                
                void OnAppModeChanged(const AppModes::AppModeChangedMessage& message);
                
                bool TryDrag();
                
                void OnViewClicked();
                
                void OnModalBackgroundTapped();

                Eegeo::Helpers::TCallback1<DesktopSettingsMenuController, const ExampleApp::SearchResultPoi::SearchResultPoiViewOpenedMessage&> m_poiOpenedHandler;
                Eegeo::Helpers::TCallback1<DesktopSettingsMenuController, const ExampleApp::SearchResultPoi::SearchResultPoiViewClosedMessage&> m_poiClosedHandler;

                void OnSearchResultPoiViewOpenedMessage(const ExampleApp::SearchResultPoi::SearchResultPoiViewOpenedMessage& message);
                void OnSearchResultPoiViewClosedMessage(const ExampleApp::SearchResultPoi::SearchResultPoiViewClosedMessage& message);

                Eegeo::Helpers::TCallback0<DesktopSettingsMenuController> m_onViewOpenedCallback;
                Eegeo::Helpers::TCallback0<DesktopSettingsMenuController> m_onViewClosedCallback;

                void OnSearchMenuOpened();
                void OnSearchMenuClosed();

            public:
                DesktopSettingsMenuController(const std::shared_ptr<Menu::View::IMenuView>& menuView,
                                       const std::shared_ptr<Menu::View::IMenuModel>& menuModel,
                                       const std::shared_ptr<Menu::View::IMenuViewModel>& menuViewModel,
                                       const std::shared_ptr<Modality::View::IModalBackgroundView>& modalBackgroundView,
                                       const std::shared_ptr<Menu::View::IMenuView>& searchMenuView,
                                       const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);

                ~DesktopSettingsMenuController();
            };
        }
    }
}
