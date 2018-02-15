// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationConfirmationController.h"
#include "IMyPinCreationConfirmationViewModel.h"
#include "IMyPinCreationConfirmationView.h"
#include "IMyPinCreationDetailsViewModel.h"
#include "ApplyScreenControl.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            MyPinCreationConfirmationController::MyPinCreationConfirmationController(
                IMyPinCreationConfirmationViewModel& viewModel,
                IMyPinCreationConfirmationView& view,
                MyPinCreationDetails::View::IMyPinCreationDetailsViewModel& detailsViewModel,
                ExampleAppMessaging::TMessageBus& messageBus,
                Metrics::IMetricsService& metricsService)
                : m_viewModel(viewModel)
                , m_view(view)
                , m_detailsViewModel(detailsViewModel)
                , m_messageBus(messageBus)
                , m_metricsService(metricsService)
                , m_dismissedCallback(this, &MyPinCreationConfirmationController::OnDismissed)
                , m_confirmedCallback(this, &MyPinCreationConfirmationController::OnConfirmed)
                , m_openedCallback(this, &MyPinCreationConfirmationController::OnOpened)
                , m_viewStateCallback(this, &MyPinCreationConfirmationController::OnViewStateChangeScreenControl)
                , m_appModeChangedHandler(this, &MyPinCreationConfirmationController::OnAppModeChangedMessage)
                , m_userInteractionEnabledChangedHandler(this, &MyPinCreationConfirmationController::OnUserInteractionEnabledChanged)
                , m_appModeAllowsOpen(true)
            {
                m_viewModel.InsertOnScreenStateChangedCallback(m_viewStateCallback);

                m_view.InsertConfirmedCallback(m_confirmedCallback);
                m_view.InsertDismissedCallback(m_dismissedCallback);
                m_viewModel.InsertOpenCallback(m_openedCallback);
                m_messageBus.SubscribeUi(m_appModeChangedHandler);
                m_messageBus.SubscribeUi(m_userInteractionEnabledChangedHandler);
                m_view.SetOnScreenStateToIntermediateValue(m_viewModel.OnScreenState());
            }

            MyPinCreationConfirmationController::~MyPinCreationConfirmationController()
            {
                m_view.RemoveConfirmedCallback(m_confirmedCallback);
                m_view.RemoveDismissedCallback(m_dismissedCallback);
                m_viewModel.RemoveOpenCallback(m_openedCallback);
                m_viewModel.RemoveOnScreenStateChangedCallback(m_viewStateCallback);
            }

            void MyPinCreationConfirmationController::OnConfirmed()
            {
                m_metricsService.SetEvent("PinCreationConfirmation: Confirmed");
                m_viewModel.Close();
                m_messageBus.Publish(ExampleApp::MyPinCreation::MyPinCreationViewStateChangedMessage(ExampleApp::MyPinCreation::Details));
                m_viewModel.RemoveFromScreen();
                m_detailsViewModel.Open();
            }

            void MyPinCreationConfirmationController::OnDismissed()
            {
                m_metricsService.SetEvent("PinCreationConfirmation: Cancelled");
                m_viewModel.Close();
                m_messageBus.Publish(ExampleApp::MyPinCreation::MyPinCreationViewStateChangedMessage(ExampleApp::MyPinCreation::Inactive));
            }
            
            void MyPinCreationConfirmationController::OnOpened()
            {
                if(m_userInteractionEnabled && m_appModeAllowsOpen)
                {
                    m_metricsService.SetEvent("UIItem: MyPinCreation");
                    MyPinCreationViewStateChangedMessage message(ExampleApp::MyPinCreation::Ring);
                    m_messageBus.Publish(message);
                }
            }

            void MyPinCreationConfirmationController::OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message)
            {
                const AppModes::SdkModel::AppMode appMode = message.GetAppMode();
                m_appModeAllowsOpen = appMode != AppModes::SdkModel::AttractMode;
                
                if(!m_appModeAllowsOpen)
                {
                   m_viewModel.TryReleaseReactorControl();
                }
                
                
                const bool transitionClosesPinCreationDialogue =
                AppModes::SdkModel::WorldMode == appMode &&
                AppModes::SdkModel::InteriorMode == m_lastAppMode;
                if(transitionClosesPinCreationDialogue)
                {
                    MyPinCreationViewStateChangedMessage message(ExampleApp::MyPinCreation::Inactive);
                    m_messageBus.Publish(message);
                    m_viewModel.RemoveFromScreen();
                }
                
                m_lastAppMode = appMode;
            }
            
            void MyPinCreationConfirmationController::OnUserInteractionEnabledChanged(const UserInteraction::UserInteractionEnabledChangedMessage& message)
            {
                m_userInteractionEnabled = message.IsEnabled();
            }

            void MyPinCreationConfirmationController::OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel &viewModel, float &state)
            {
                ScreenControl::View::Apply(m_viewModel, m_view);
            }
        }
    }
}
