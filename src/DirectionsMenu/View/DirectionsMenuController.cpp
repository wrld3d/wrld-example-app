// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionsMenuController.h"

#include "IMenuOption.h"
#include "IModalBackgroundView.h"
#include "IDirectionsMenuView.h"
#include "SearchResultSectionItemSelectedMessage.h"
#include "DirectionQueryResponseReceivedMessage.h"

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
                                     ExampleAppMessaging::TMessageBus& messageBus)
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

            {
                m_directionsMenuView.InsertSearchPeformedCallback(m_searchPerformedCallbacks);
                m_directionsMenuView.InsertSearchClearedCallback(m_searchClearedCallbacks);
                m_directionsMenuView.InsertWayPointSelectedCallback(m_wayPointSelectedCallbacks);
                m_directionsMenuView.InsertExitDirectionsCallback(m_exitDirectionsCallbacks);
                
                Menu::View::IMenuModel& searchSectionMenuModel = m_searchSectionViewModel.GetModel();
                searchSectionMenuModel.InsertItemAddedCallback(m_onSearchItemAddedCallback);
                searchSectionMenuModel.InsertItemRemovedCallback(m_onSearchItemRemovedCallback);
                
                
                m_viewModel.InsertOpenStateChangedCallback(m_onOpenStateChangedCallback);
                m_modalBackgroundView.InsertTappedCallback(m_onModalBackgroundTappedCallback);
                m_messageBus.SubscribeUi(m_appModeChangedCallback);
                m_messageBus.SubscribeUi(m_directionsMenuStateChangedCallback);
                
            }
            
            DirectionsMenuController::~DirectionsMenuController()
            {
                m_modalBackgroundView.RemoveTappedCallback(m_onModalBackgroundTappedCallback);
                m_viewModel.RemoveOpenStateChangedCallback(m_onOpenStateChangedCallback);
                
                m_directionsMenuView.RemoveSearchPeformedCallback(m_searchPerformedCallbacks);
                m_directionsMenuView.RemoveSearchClearedCallback(m_searchClearedCallbacks);
                m_directionsMenuView.RemoveWayPointSelectedCallback(m_wayPointSelectedCallbacks);
                m_directionsMenuView.RemoveExitDirectionsCallback(m_exitDirectionsCallbacks);
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
            
            void DirectionsMenuController::OnSearch(const std::string& searchQuery)
            {
                // Publish message Here
                m_messageBus.Publish(DirectionResultSection::DirectionQueryResponseReceivedMessage("temp Query String"));
                
            }
            
            void DirectionsMenuController::OnSearchCleared()
            {
            
            }
            
            void DirectionsMenuController::OnWayPointItemSelected(int& index)
            {
                
                m_searchSectionViewModel.GetItemAtIndex(index).MenuOption().Select();
                
            }
            
            void DirectionsMenuController::OnExitDirectionsClicked()
            {
                MenuController::OnViewClicked();
             
                DirectionsMenuInitiation::DirectionsMenuStateChangedMessage message(ExampleApp::DirectionsMenuInitiation::Inactive);
                m_messageBus.Publish(message);
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