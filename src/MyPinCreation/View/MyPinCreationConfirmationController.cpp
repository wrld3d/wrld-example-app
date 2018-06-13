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
                , m_userInteractionEnabled(true)
                , m_dismissedCallback(this, &MyPinCreationConfirmationController::OnDismissed)
                , m_confirmedCallback(this, &MyPinCreationConfirmationController::OnConfirmed)
                , m_openedCallback(this, &MyPinCreationConfirmationController::OnOpened)
                , m_viewStateCallback(this, &MyPinCreationConfirmationController::OnViewStateChangeScreenControl)
                , m_appModeAllowsOpen(true)
            {
                m_viewModel.InsertOnScreenStateChangedCallback(m_viewStateCallback);

                m_view.InsertConfirmedCallback(m_confirmedCallback);
                m_view.InsertDismissedCallback(m_dismissedCallback);
                m_viewModel.InsertOpenCallback(m_openedCallback);
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

            void MyPinCreationConfirmationController::OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel &viewModel)
            {
                ScreenControl::View::Apply(m_viewModel, m_view);
            }
        }
    }
}
