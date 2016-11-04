// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionsMenuController.h"

#include "IMenuOption.h"
#include "IModalBackgroundView.h"
#include "IDirectionsMenuView.h"
#include "SearchResultSectionItemSelectedMessage.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace View
        {
            DirectionsMenuController::DirectionsMenuController(Menu::View::IMenuModel& model,
                                     Menu::View::IMenuViewModel& viewModel,
                                     Menu::View::IMenuView& view,
                                     DirectionsMenu::View::IDirectionsMenuView& directionsMenuView,
                                    Menu::View::IMenuSectionViewModel& searchSectionViewModel,
                                     Modality::View::IModalBackgroundView& modalBackgroundView,
                                     ExampleAppMessaging::TMessageBus& messageBus,
                                     Eegeo::Location::ILocationService& locationService)
                        : Menu::View::MenuController(model, viewModel, view, messageBus)
                        , m_directionsMenuView(directionsMenuView)
                        , m_searchSectionViewModel(searchSectionViewModel)
                        , m_modalBackgroundView(modalBackgroundView)
                        , m_messageBus(messageBus)
                        , m_appModeAllowsOpen(true)
                        , m_appModeChangedCallback(this, &DirectionsMenuController::OnAppModeChanged)
                        , m_directionsMenuStateChangedCallback(this, &DirectionsMenuController::OnDirectionsMenuStateChanged)
                        , m_searchPerformedCallbacks(this, &DirectionsMenuController::OnSearch)
                        , m_searchClearedCallbacks(this, &DirectionsMenuController::OnSearchCleared)
                        , m_wayPointSelectedCallbacks(this, &DirectionsMenuController::OnWayPointItemSelected)
                        , m_exitDirectionsCallbacks(this, &DirectionsMenuController::OnExitDirectionsClicked)
                        , m_onModalBackgroundTappedCallback(this, &DirectionsMenuController::OnModalBackgroundTapped)
                        , m_onOpenStateChangedCallback(this, &DirectionsMenuController::OnOpenStateChanged)
                        , m_onSearchItemAddedCallback(this, &DirectionsMenuController::OnSearchItemAdded)
                        , m_onSearchItemRemovedCallback(this, &DirectionsMenuController::OnSearchItemRemoved)
                        , m_directionsMenuHighlightItemCallback(this, &DirectionsMenuController::OnDirectionsHighlightItem)
                        , m_onStartLocationChangedCallback(this,&DirectionsMenuController::OnStartLocationChanged)
                        , m_onEndLocationChangedCallback(this, &DirectionsMenuController::OnEndLocationChanged)
                        , m_onStartLocationResponseReceivedCallback(this, &DirectionsMenuController::OnGeoNamesStartLocationResponseReceived)
                        , m_isExitDirections(false)
                        , m_locationService(locationService)

            {
                m_directionsMenuView.InsertSearchPeformedCallback(m_searchPerformedCallbacks);
                m_directionsMenuView.InsertSearchClearedCallback(m_searchClearedCallbacks);
                m_directionsMenuView.InsertWayPointSelectedCallback(m_wayPointSelectedCallbacks);
                m_directionsMenuView.InsertExitDirectionsCallback(m_exitDirectionsCallbacks);
                m_directionsMenuView.InsertStartLocationChangedCallback(m_onStartLocationChangedCallback);
                m_directionsMenuView.InsertEndLocationChangedCallback(m_onEndLocationChangedCallback);
                
                Menu::View::IMenuModel& searchSectionMenuModel = m_searchSectionViewModel.GetModel();
                searchSectionMenuModel.InsertItemAddedCallback(m_onSearchItemAddedCallback);
                searchSectionMenuModel.InsertItemRemovedCallback(m_onSearchItemRemovedCallback);
                
                
                m_viewModel.InsertOpenStateChangedCallback(m_onOpenStateChangedCallback);
                m_modalBackgroundView.InsertTappedCallback(m_onModalBackgroundTappedCallback);
                m_messageBus.SubscribeUi(m_appModeChangedCallback);
                m_messageBus.SubscribeUi(m_directionsMenuStateChangedCallback);
                m_messageBus.SubscribeUi(m_directionsMenuHighlightItemCallback);
                m_messageBus.SubscribeUi(m_onStartLocationResponseReceivedCallback);
                
            }
            
            DirectionsMenuController::~DirectionsMenuController()
            {
                m_modalBackgroundView.RemoveTappedCallback(m_onModalBackgroundTappedCallback);
                m_viewModel.RemoveOpenStateChangedCallback(m_onOpenStateChangedCallback);
                
                m_directionsMenuView.RemoveSearchPeformedCallback(m_searchPerformedCallbacks);
                m_directionsMenuView.RemoveSearchClearedCallback(m_searchClearedCallbacks);
                m_directionsMenuView.RemoveWayPointSelectedCallback(m_wayPointSelectedCallbacks);
                m_directionsMenuView.RemoveExitDirectionsCallback(m_exitDirectionsCallbacks);
                
                Menu::View::IMenuModel& searchSectionMenuModel = m_searchSectionViewModel.GetModel();
                searchSectionMenuModel.RemoveItemAddedCallback(m_onSearchItemAddedCallback);
                searchSectionMenuModel.RemoveItemAddedCallback(m_onSearchItemRemovedCallback);
                
                m_messageBus.UnsubscribeUi(m_appModeChangedCallback);
                m_messageBus.UnsubscribeUi(m_directionsMenuStateChangedCallback);
                m_messageBus.UnsubscribeUi(m_directionsMenuHighlightItemCallback);
                m_messageBus.UnsubscribeUi(m_onStartLocationResponseReceivedCallback);

            }
            
            void DirectionsMenuController::OnSearchItemAdded(Menu::View::MenuItemModel& item)
            {
                m_presentationDirty = true;
            }
            
            void DirectionsMenuController::OnSearchItemRemoved(Menu::View::MenuItemModel& item)
            {
                m_presentationDirty = true;
            }
            
            void DirectionsMenuController::OnOpenStateChanged(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState)
            {
                if(openState != 1.f)
                {

                }
            }
            
            void DirectionsMenuController::OnViewClosed()
            {
                MenuController::OnViewClosed();
                if (m_isExitDirections)
                {
                    m_isExitDirections = false;
                    DirectionsMenuInitiation::DirectionsMenuStateChangedMessage message(ExampleApp::DirectionsMenuInitiation::Inactive);
                    m_messageBus.Publish(message);
                    
                    RefreshPresentation();
                }
                
            }
            void DirectionsMenuController::OnSearch(const Eegeo::Space::LatLong& start,const Eegeo::Space::LatLong& end)
            {
                Eegeo::Space::LatLong currentLatLong = Eegeo::Space::LatLong::FromDegrees(start.GetLatitudeInDegrees(), start.GetLongitudeInDegrees());
                if (currentLatLong.GetLongitudeInDegrees() == 0 && currentLatLong.GetLongitudeInDegrees() == 0)
                {
                    m_locationService.GetLocation(currentLatLong);
                }

                const Eegeo::Space::LatLongAltitude startLoc = Eegeo::Space::LatLongAltitude::FromDegrees(currentLatLong.GetLatitudeInDegrees(), currentLatLong.GetLongitudeInDegrees(),0.0);
                const Eegeo::Space::LatLongAltitude endLoc = Eegeo::Space::LatLongAltitude::FromDegrees(end.GetLatitudeInDegrees(), end.GetLongitudeInDegrees(),0.0);

//                const Eegeo::Space::LatLongAltitude startLoc = Eegeo::Space::LatLongAltitude::FromDegrees(56.459917,-2.984219,0.0);
//                const Eegeo::Space::LatLongAltitude endLoc = Eegeo::Space::LatLongAltitude::FromDegrees(56.459778,-2.977156,0.0);

                
                m_messageBus.Publish(ExampleApp::DirectionsMenu::DirectionMenuFindDirectionMessage(startLoc,endLoc,true));
                
            }
            
            void DirectionsMenuController::OnStartLocationChanged(const std::string& startLocationQuery)
            {
                Eegeo_TTY("OnStartLocationChanged");
                m_messageBus.Publish(ExampleApp::DirectionsMenu::DirectionMenuGetGeoNamesMessage(startLocationQuery, false, true));
            }
            
            void DirectionsMenuController::OnEndLocationChanged(const std::string& startLocationQuery)
            {
                Eegeo_TTY("OnEndLocationChanged");
                m_messageBus.Publish(ExampleApp::DirectionsMenu::DirectionMenuGetGeoNamesMessage(startLocationQuery, false, false));
            }
            
            void DirectionsMenuController::OnGeoNamesStartLocationResponseReceived(const DirectionsMenu::DirectionMenuGeoNamesResponseReceivedMessage& message)
            {
                if(message.IsStartLocationActive())
                {
                    m_directionsMenuView.SetGeoNamesStartSuggestions(message.SearchResults());
                }
                else
                {
                    m_directionsMenuView.SetGeoNamesEndSuggestions(message.SearchResults());
                }
            }
            
            void DirectionsMenuController::OnSearchCleared()
            {
            
            }
                                         
            void DirectionsMenuController::OnDirectionsHighlightItem(const DirectionsMenuInitiation::DirectionsMenuItemHighlightMessage& message)
            {
                
                m_directionsMenuView.HighlightListItem(message.GetSelectedItemIndex());
                MenuController::OnViewClicked();
            }
            
            void DirectionsMenuController::OnWayPointItemSelected(int& index)
            {
                
                m_searchSectionViewModel.GetItemAtIndex(index).MenuOption().Select();
                m_directionsMenuView.HighlightListItem(index);
                
            }
            
            void DirectionsMenuController::OnExitDirectionsClicked()
            {
                
                MenuController::OnViewClicked();
                m_isExitDirections = true;

            }
            
            void DirectionsMenuController::OnAppModeChanged(const AppModes::AppModeChangedMessage& message)
            {
                
            }
            
            void DirectionsMenuController::OnDirectionsMenuStateChanged(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage& message)
            {
                if (message.GetDirectionsMenuStage() == DirectionsMenuInitiation::Active) {
                    MenuController::OnViewClicked();
                }
            }
            
            bool DirectionsMenuController::TryDrag()
            {
                return MenuController::TryDrag();
            }
            
            void DirectionsMenuController::OnViewClicked()
            {
                MenuController::OnViewClicked();
            }
            
            void DirectionsMenuController::OnModalBackgroundTapped()
            {
                if(!m_appModeAllowsOpen)
                {
                    return;
                }
                
                if(m_viewModel.IsFullyOpen())
                {
                    m_viewModel.Close();
                }
            }
            
            void DirectionsMenuController::RefreshPresentation()
            {
                MenuController::RefreshPresentation();
                
                if(!m_viewModel.IsFullyClosed())
                {
                    m_directionsMenuView.SetSearchSection(m_searchSectionViewModel);
                }
            }

            bool DirectionsMenuController::IsFullyOpen() const
            {
                return m_viewModel.IsFullyOpen();
            }

            void DirectionsMenuController::UpdateOpenState()
            {
                m_viewModel.UpdateOpenState(1.0f);
            }
        }
    }
}