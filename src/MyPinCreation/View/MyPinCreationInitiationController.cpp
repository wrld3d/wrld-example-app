// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationInitiationController.h"
#include "IMyPinCreationInitiationView.h"
#include "IMyPinCreationInitiationViewModel.h"
#include "IMyPinCreationConfirmationViewModel.h"
#include "ApplyScreenControl.h"
#include "MyPinCreationViewStateChangedMessage.h"
#include "MyPinCreationStage.h"
#include "VirtualKeyboardStateChangedMessage.h"

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
                , m_userInteractionEnabled(true)
                , m_appModeAllowsOpen(true)
                , m_selectedCallback(this, &MyPinCreationInitiationController::OnSelected)
                , m_viewStateCallback(this, &MyPinCreationInitiationController::OnViewStateChangeScreenControl)
                , m_appModeChangedHandler(this, &MyPinCreationInitiationController::OnAppModeChangedMessage)
                , m_virtualKeyboardStateChangedMessageHandler(this, &MyPinCreationInitiationController::OnVirtualKeyboardStateChangedMessage)
                , m_userInteractionEnabledChangedHandler(this, &MyPinCreationInitiationController::OnUserInteractionEnabledChanged)
            {
                m_view.InsertSelectedCallback(m_selectedCallback);
                m_viewModel.InsertOnScreenStateChangedCallback(m_viewStateCallback);
                m_messageBus.SubscribeUi(m_appModeChangedHandler);
                m_messageBus.SubscribeUi(m_virtualKeyboardStateChangedMessageHandler);
                m_messageBus.SubscribeUi(m_userInteractionEnabledChangedHandler);
            }

            MyPinCreationInitiationController::~MyPinCreationInitiationController()
            {
                m_messageBus.UnsubscribeUi(m_userInteractionEnabledChangedHandler);
                m_messageBus.UnsubscribeUi(m_virtualKeyboardStateChangedMessageHandler);
                m_messageBus.UnsubscribeUi(m_appModeChangedHandler);
                m_viewModel.RemoveOnScreenStateChangedCallback(m_viewStateCallback);
                m_view.RemoveSelectedCallback(m_selectedCallback);
            }

            void MyPinCreationInitiationController::OnSelected()
            {
                if(m_userInteractionEnabled && m_appModeAllowsOpen && m_confirmationViewModel.TryOpen())
                {
                    m_metricsService.SetEvent("UIItem: MyPinCreation");
                    MyPinCreationViewStateChangedMessage message(ExampleApp::MyPinCreation::Ring);
                    m_messageBus.Publish(message);
                }
            }

            void MyPinCreationInitiationController::OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel &viewModel, float &state)
            {
                ScreenControl::View::Apply(m_viewModel, m_view);
            }
            
            void MyPinCreationInitiationController::OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message)
            {
                m_appModeAllowsOpen = message.GetAppMode() != AppModes::SdkModel::AttractMode;
                
                if(m_appModeAllowsOpen)
                {
                    m_viewModel.AddToScreen();
                }
                else
                {
                    m_viewModel.RemoveFromScreen();
                    m_confirmationViewModel.TryReleaseReactorControl();
                }
            }

            void MyPinCreationInitiationController::OnVirtualKeyboardStateChangedMessage(const VirtualKeyboard::VirtualKeyboardStateChangedMessage& message)
            {
                if (message.IsVirtualKeyboardVisible())
                {
                    m_viewModel.RemoveFromScreen();
                }
                else
                {
                    m_viewModel.AddToScreen();
                }
            }

            void MyPinCreationInitiationController::OnUserInteractionEnabledChanged(const UserInteraction::UserInteractionEnabledChangedMessage& message)
            {
                m_userInteractionEnabled = message.IsEnabled();
            }
        }
    }
}
