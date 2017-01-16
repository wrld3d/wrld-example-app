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
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Modality::View::IModalBackgroundView& m_modalBackgroundView;
                bool m_appModeAllowsOpen;
                bool m_isControlOpen[Control::Num];
                
                Eegeo::Helpers::TCallback0<DesktopSettingsMenuController> m_onModalBackgroundTappedCallback;

                Menu::View::IMenuView& m_searchMenuView;
                
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
                DesktopSettingsMenuController(Menu::View::IMenuView& menuView,
                                       Menu::View::IMenuModel& menuModel,
                                       Menu::View::IMenuViewModel& menuViewModel,
                                       Modality::View::IModalBackgroundView& modalBackgroundView,
                                       Menu::View::IMenuView& searchMenuView,
                                       ExampleAppMessaging::TMessageBus& messageBus);

                ~DesktopSettingsMenuController();
            };
        }
    }
}
