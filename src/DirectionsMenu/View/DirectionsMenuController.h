// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuController.h"
#include "Modality.h"
#include "DirectionsMenu.h"
#include "IModalityController.h"
#include "DirectionsMenuStateChangedMessage.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace View
        {
            class DirectionsMenuController : public Menu::View::MenuController
            {
            private:
                Modality::View::IModalBackgroundView& m_modalBackgroundView;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                IDirectionsMenuView& m_directionsMenuView;
                Eegeo::Helpers::TCallback1<DirectionsMenuController, const std::string&> m_searchPerformedCallbacks;
                Eegeo::Helpers::TCallback0<DirectionsMenuController> m_searchClearedCallbacks;
                Eegeo::Helpers::TCallback1<DirectionsMenuController, int> m_wayPointSelectedCallbacks;
                Eegeo::Helpers::TCallback0<DirectionsMenuController> m_exitDirectionsCallbacks;
                bool m_appModeAllowsOpen;

                Eegeo::Helpers::TCallback2<DirectionsMenuController, OpenableControl::View::IOpenableControlViewModel&, float> m_onOpenStateChangedCallback;
                Eegeo::Helpers::TCallback1<DirectionsMenuController, const AppModes::AppModeChangedMessage&> m_appModeChangedCallback;
                Eegeo::Helpers::TCallback1<DirectionsMenuController, const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage&> m_directionsMenuStateChangedCallback;
                
                Eegeo::Helpers::TCallback0<DirectionsMenuController> m_onModalBackgroundTappedCallback;
                
                void OnOpenStateChanged(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState);
                
                void OnAppModeChanged(const AppModes::AppModeChangedMessage& message);
                
                void OnDirectionsMenuStateChanged(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage& message);
                
                bool TryDrag();
                
                void OnViewClicked();
                
                void OnModalBackgroundTapped();
                
                void OnSearch(const std::string& searchQuery);
                
                void OnSearchCleared();
                
                void OnWayPointItemSelected(int& index);
                
                void OnExitDirectionsClicked();
                
            protected:
                
                virtual void RefreshPresentation();
                bool IsFullyOpen() const;
                void UpdateOpenState();
                
            public:
                DirectionsMenuController(Menu::View::IMenuModel& model,
                                         Menu::View::IMenuViewModel& viewModel,
                                         Menu::View::IMenuView& view,
                                         DirectionsMenu::View::IDirectionsMenuView& directionsMenuView,
                                         Modality::View::IModalBackgroundView& modalBackgroundView,
                                         ExampleAppMessaging::TMessageBus& messageBus);
                
                virtual ~DirectionsMenuController();
            };
        }
    }
}