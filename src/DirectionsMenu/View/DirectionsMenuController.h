// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuController.h"
#include "Modality.h"
#include "DirectionsMenu.h"
#include "IModalityController.h"
#include "DirectionsMenuStateChangedMessage.h"
#include "DirectionsMenuItemHighlightMessage.h"
#include "DirectionMenuGeoNamesResponseReceivedMessage.h"
#include "ILocationService.h"


namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace View
        {
            class DirectionsMenuController : public Menu::View::MenuController
            {
            private:
                Eegeo::Location::ILocationService& m_locationService;
                Modality::View::IModalBackgroundView& m_modalBackgroundView;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                IDirectionsMenuView& m_directionsMenuView;
                Menu::View::IMenuSectionViewModel& m_searchSectionViewModel;
                
                Eegeo::Helpers::TCallback2<DirectionsMenuController, const Eegeo::Space::LatLong&,const Eegeo::Space::LatLong&> m_searchPerformedCallbacks;
                Eegeo::Helpers::TCallback0<DirectionsMenuController> m_searchClearedCallbacks;
                Eegeo::Helpers::TCallback1<DirectionsMenuController, int> m_wayPointSelectedCallbacks;
                Eegeo::Helpers::TCallback0<DirectionsMenuController> m_exitDirectionsCallbacks;
                bool m_appModeAllowsOpen;
                bool m_isExitDirections;

                Eegeo::Helpers::TCallback2<DirectionsMenuController, OpenableControl::View::IOpenableControlViewModel&, float> m_onOpenStateChangedCallback;
                Eegeo::Helpers::TCallback1<DirectionsMenuController, const AppModes::AppModeChangedMessage&> m_appModeChangedCallback;
                Eegeo::Helpers::TCallback1<DirectionsMenuController, const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage&> m_directionsMenuStateChangedCallback;
                Eegeo::Helpers::TCallback1<DirectionsMenuController, const DirectionsMenuInitiation::DirectionsMenuItemHighlightMessage&> m_directionsMenuHighlightItemCallback;
                
                Eegeo::Helpers::TCallback0<DirectionsMenuController> m_onModalBackgroundTappedCallback;
                Eegeo::Helpers::TCallback1<DirectionsMenuController, Menu::View::MenuItemModel> m_onSearchItemAddedCallback;
                Eegeo::Helpers::TCallback1<DirectionsMenuController, Menu::View::MenuItemModel> m_onSearchItemRemovedCallback;

                Eegeo::Helpers::TCallback1<DirectionsMenuController,const std::string&>  m_onStartLocationChangedCallback;
                Eegeo::Helpers::TCallback1<DirectionsMenuController,const std::string&>  m_onEndLocationChangedCallback;
                
                
                Eegeo::Helpers::TCallback1<DirectionsMenuController, const DirectionsMenu::DirectionMenuGeoNamesResponseReceivedMessage&> m_onStartLocationResponseReceivedCallback;
                
                
                void OnOpenStateChanged(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState);
                void OnViewClosed();

                void OnAppModeChanged(const AppModes::AppModeChangedMessage& message);
                
                void OnDirectionsMenuStateChanged(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage& message);
                void OnDirectionsHighlightItem(const DirectionsMenuInitiation::DirectionsMenuItemHighlightMessage& message);
                
                bool TryDrag();
                
                void OnViewClicked();
                
                void OnModalBackgroundTapped();
                
                void OnSearch(const Eegeo::Space::LatLong& start,const Eegeo::Space::LatLong& end);
                
                void OnSearchCleared();
                
                void OnWayPointItemSelected(int& index);
                
                void OnExitDirectionsClicked();
                
                void OnSearchItemAdded(Menu::View::MenuItemModel& item);
                
                void OnSearchItemRemoved(Menu::View::MenuItemModel& item);
                
                void OnStartLocationChanged(const std::string& startLocationQuery);
                
                void OnEndLocationChanged(const std::string& startLocationQuery);
                
                void OnGeoNamesStartLocationResponseReceived(const DirectionsMenu::DirectionMenuGeoNamesResponseReceivedMessage& message);
                
            protected:
                
                virtual void RefreshPresentation();
                bool IsFullyOpen() const;
                void UpdateOpenState();
                
            public:
                DirectionsMenuController(Menu::View::IMenuModel& model,
                                         Menu::View::IMenuViewModel& viewModel,
                                         Menu::View::IMenuView& view,
                                         DirectionsMenu::View::IDirectionsMenuView& directionsMenuView,
                                         Menu::View::IMenuSectionViewModel& searchSectionViewModel,
                                         Modality::View::IModalBackgroundView& modalBackgroundView,
                                         ExampleAppMessaging::TMessageBus& messageBus,
                                         Eegeo::Location::ILocationService& locationService);
                
                virtual ~DirectionsMenuController();
            };
        }
    }
}