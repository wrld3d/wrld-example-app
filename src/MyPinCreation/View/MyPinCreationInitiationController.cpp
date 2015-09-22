// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationInitiationController.h"
#include "IMyPinCreationInitiationView.h"
#include "IMyPinCreationInitiationViewModel.h"
#include "IMyPinCreationConfirmationViewModel.h"
#include "ApplyScreenControl.h"
#include "MyPinCreationViewStateChangedMessage.h"
#include "MyPinCreationStage.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            MyPinCreationInitiationController::MyPinCreationInitiationController(
                IMyPinCreationInitiationViewModel& viewModel,
                IMyPinCreationInitiationView& view,
                IMyPinCreationConfirmationViewModel& confirmationViewModel,
                ExampleAppMessaging::TMessageBus& messageBus,
                Metrics::IMetricsService& metricsService)
                : m_view(view)
                , m_viewModel(viewModel)
                , m_confirmationViewModel(confirmationViewModel)
                , m_messageBus(messageBus)
                , m_metricsService(metricsService)
                , m_appModeAllowsOpen(true)
                , m_selectedCallback(this, &MyPinCreationInitiationController::OnSelected)
                , m_viewStateCallback(this, &MyPinCreationInitiationController::OnViewStateChangeScreenControl)
                , m_appModeChangedMessage(this, &MyPinCreationInitiationController::OnAppModeChanged)
            {
                m_messageBus.SubscribeUi(m_appModeChangedMessage);
                
                m_view.InsertSelectedCallback(m_selectedCallback);
                m_viewModel.InsertOnScreenStateChangedCallback(m_viewStateCallback);
            }

            MyPinCreationInitiationController::~MyPinCreationInitiationController()
            {
                m_viewModel.RemoveOnScreenStateChangedCallback(m_viewStateCallback);
                m_view.RemoveSelectedCallback(m_selectedCallback);
                
                m_messageBus.UnsubscribeUi(m_appModeChangedMessage);
            }

            void MyPinCreationInitiationController::OnSelected()
            {
                if(m_appModeAllowsOpen && m_confirmationViewModel.TryOpen())
                {
                    m_metricsService.SetEvent("UIItem: MyPinCreation");
                    MyPinCreationViewStateChangedMessage message(ExampleApp::MyPinCreation::Ring);
                    m_messageBus.Publish(message);
                }
            }

            void MyPinCreationInitiationController::OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel &viewModel, float &state)
            {
                if(state > 0.001f && !m_appModeAllowsOpen)
                {
                    return;
                }
                
                ScreenControl::View::Apply(m_viewModel, m_view);
            }
            
            void MyPinCreationInitiationController::OnAppModeChanged(const AppModes::AppModeChangedMessage& message)
            {
                if(message.GetAppMode() == AppModes::SdkModel::InteriorMode)
                {
                    m_appModeAllowsOpen = false;
                    m_view.SetFullyOffScreen();
                }
                else
                {
                    m_appModeAllowsOpen = true;
                    m_view.SetFullyOnScreen();
                }
            }
        }
    }
}
