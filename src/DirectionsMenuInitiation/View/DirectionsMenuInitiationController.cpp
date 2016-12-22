// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionsMenuInitiationController.h"
#include "IDirectionsMenuInitiationView.h"
#include "IDirectionsMenuInitiationViewModel.h"
#include "IMyPinCreationConfirmationViewModel.h"
#include "ApplyScreenControl.h"
#include "DirectionsMenuStateChangedMessage.h"
#include "DirectionsMenuStage.h"

namespace ExampleApp
{
    namespace DirectionsMenuInitiation
    {
        namespace View
        {
            DirectionsMenuInitiationController::DirectionsMenuInitiationController(
                IDirectionsMenuInitiationViewModel& viewModel,
                IDirectionsMenuInitiationView& view,
                ExampleAppMessaging::TMessageBus& messageBus,
                Metrics::IMetricsService& metricsService)
                : m_view(view)
                , m_viewModel(viewModel)
                , m_messageBus(messageBus)
                , m_appModeAllowsOpen(true)
                , m_selectedCallback(this, &DirectionsMenuInitiationController::OnToggle)
                , m_viewStateCallback(this, &DirectionsMenuInitiationController::OnViewStateChangeScreenControl)
                , m_appModeChangedHandler(this, &DirectionsMenuInitiationController::OnAppModeChangedMessage)
            {
                m_view.InsertToggleCallback(m_selectedCallback);
                m_viewModel.InsertOnScreenStateChangedCallback(m_viewStateCallback);
                m_messageBus.SubscribeUi(m_appModeChangedHandler);
            }

            DirectionsMenuInitiationController::~DirectionsMenuInitiationController()
            {
                m_messageBus.UnsubscribeUi(m_appModeChangedHandler);
                m_viewModel.RemoveOnScreenStateChangedCallback(m_viewStateCallback);
                m_view.RemoveToggleCallback(m_selectedCallback);
            }

            void DirectionsMenuInitiationController::OnToggle(bool& toggle)
            {
                if(m_appModeAllowsOpen)
                {
                    DirectionsMenuStateChangedMessage message(ExampleApp::DirectionsMenuInitiation::Active,false);
                    m_messageBus.Publish(message);
                }
            }

            void DirectionsMenuInitiationController::OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel &viewModel, float &state)
            {
                ScreenControl::View::Apply(m_viewModel, m_view);
            }
            
            void DirectionsMenuInitiationController::OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message)
            {
                m_appModeAllowsOpen = message.GetAppMode() != AppModes::SdkModel::TourMode;
                
                if(m_appModeAllowsOpen)
                {
                    m_viewModel.AddToScreen();
                }
                else
                {
                    m_viewModel.RemoveFromScreen();
                }
            }

        }
    }
}
