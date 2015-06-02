// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInteriorsView.h"
#include "InteriorsController.h"
#include "ICallback.h"
#include "BidirectionalBus.h"
#include "IMyPinCreationInitiationViewModel.h"
#include "IMyPinCreationConfirmationViewModel.h"
#include "IMenuViewModel.h"
#include "IScreenControlViewModel.h"
#include "ApplyScreenControl.h"
#include <sstream>

namespace ExampleApp
{
    namespace Interiors
    {
        namespace View
        {
            class InteriorsViewController
            {
            public:
                
                InteriorsViewController(IInteriorsView& view,
                                        Eegeo::Resources::Interiors::InteriorsController& interiorController,
                                        ScreenControl::View::IScreenControlViewModel& viewModel,
                                        ExampleAppMessaging::TMessageBus& messageBus,
                                        MyPinCreation::View::IMyPinCreationInitiationViewModel& initiationViewModel,
                                        ExampleApp::Menu::View::IMenuViewModel& secondaryMenuViewModel,
                                        ExampleApp::Menu::View::IMenuViewModel& searchResultMenuViewModel,
                                        ScreenControl::View::IScreenControlViewModel& flattenViewModel,
                                        ScreenControl::View::IScreenControlViewModel& compassViewModel)
                : m_view(view)
                , m_viewModel(viewModel)
                , m_interiorController(interiorController)
                , m_messageBus(messageBus)
                , m_initiationViewModel(initiationViewModel)
                , m_secondaryMenuViewModel(secondaryMenuViewModel)
                , m_searchResultMenuViewModel(searchResultMenuViewModel)
                , m_flattenViewModel(flattenViewModel)
                , m_compassViewModel(compassViewModel)
                , m_dismissedCallback(this, &InteriorsViewController::OnDismiss)
                , m_floorSelectedCallback(this, &InteriorsViewController::OnFloorSelected)
                , m_stateChangedCallback(this, &InteriorsViewController::OnStateChanged)
                , m_viewStateCallback(this, &InteriorsViewController::OnViewStateChangeScreenControl)
                {
                    m_interiorController.RegisterStateChangedCallback(m_stateChangedCallback);
                    
                    m_viewModel.InsertOnScreenStateChangedCallback(m_viewStateCallback);
                    
                    m_view.InsertDismissedCallback(m_dismissedCallback);
                    m_view.InsertFloorSelectedCallback(m_floorSelectedCallback);
                }
                
                ~InteriorsViewController()
                {
                    m_view.RemoveDismissedCallback(m_dismissedCallback);
                    m_view.RemoveFloorSelectedCallback(m_floorSelectedCallback);
                    
                    m_viewModel.RemoveOnScreenStateChangedCallback(m_viewStateCallback);
                    
                    m_interiorController.UnregisterStateChangedCallback(m_stateChangedCallback);
                }
                
            private:
                
                void OnDismiss()
                {
                    if(m_interiorController.ShowingInterior())
                    {
                        m_view.OnDismissed();
                        m_interiorController.ExitInterior();
                    }
                }
                
                void OnFloorSelected(int& selected)
                {
                    std::stringstream content;
                    content << "Floor " << (selected+1);
                    m_interiorController.SelectFloor(selected);
                    m_view.SetFloorName(content.str());
                    
                }
                
                void OnStateChanged()
                {
                    if(m_interiorController.ShowingInterior())
                    {
                        // Show
                        m_view.SetFloorCount(m_interiorController.GetFloorCount());
                        int initialFloor = m_interiorController.GetCurrentFloorNumber();
                        OnFloorSelected(initialFloor);
                        
                        m_viewModel.AddToScreen();
                        
                        m_initiationViewModel.RemoveFromScreen();
                        m_secondaryMenuViewModel.RemoveFromScreen();
                        m_searchResultMenuViewModel.RemoveFromScreen();
                        m_flattenViewModel.RemoveFromScreen();
                        m_compassViewModel.RemoveFromScreen();
                        m_messageBus.Publish(WorldPins::WorldPinsVisibilityMessage(false));
                        m_messageBus.Publish(GpsMarker::GpsMarkerVisibilityMessage(false));
                    }
                    else
                    {
                        // Hide.
                        m_viewModel.RemoveFromScreen();
                        
                        // Hide everything else.
                        m_initiationViewModel.AddToScreen();
                        m_secondaryMenuViewModel.AddToScreen();
                        m_searchResultMenuViewModel.AddToScreen();
                        m_flattenViewModel.AddToScreen();
                        m_compassViewModel.AddToScreen();
                        m_messageBus.Publish(WorldPins::WorldPinsVisibilityMessage(true));
                        m_messageBus.Publish(GpsMarker::GpsMarkerVisibilityMessage(true));
                    }
                }
                
                void OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel &viewModel, float &state)
                {
                    ScreenControl::View::Apply(m_viewModel, m_view);
                }
                
                IInteriorsView& m_view;
                ScreenControl::View::IScreenControlViewModel& m_viewModel;
                Eegeo::Resources::Interiors::InteriorsController& m_interiorController;
                
                Eegeo::Helpers::TCallback0<InteriorsViewController> m_dismissedCallback;
                Eegeo::Helpers::TCallback1<InteriorsViewController, int> m_floorSelectedCallback;
                Eegeo::Helpers::TCallback0<InteriorsViewController> m_stateChangedCallback;
                Eegeo::Helpers::TCallback2<InteriorsViewController, ScreenControl::View::IScreenControlViewModel&, float> m_viewStateCallback;
                
                MyPinCreation::View::IMyPinCreationInitiationViewModel& m_initiationViewModel;
                ExampleApp::Menu::View::IMenuViewModel& m_secondaryMenuViewModel;
                ExampleApp::Menu::View::IMenuViewModel& m_searchResultMenuViewModel;
                ScreenControl::View::IScreenControlViewModel& m_flattenViewModel;
                ScreenControl::View::IScreenControlViewModel& m_compassViewModel;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                
            };
        }
    }
}