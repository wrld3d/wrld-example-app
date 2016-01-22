// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationDetailsController.h"
#include "IMyPinCreationDetailsView.h"
#include "IMyPinCreationDetailsViewModel.h"
#include "MyPinCreationViewStateChangedMessage.h"
#include "MyPinCreationViewSavePinMessage.h"
#include "ConnectivityChangedViewMessage.h"
#include <string>

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            MyPinCreationDetailsController::MyPinCreationDetailsController(
                IMyPinCreationDetailsView& view,
                IMyPinCreationDetailsViewModel& viewModel,
                ExampleAppMessaging::TMessageBus& messageBus,
                Metrics::IMetricsService& metricsService
            )
                : m_view(view)
                , m_viewModel(viewModel)
                , m_messageBus(messageBus)
                , m_metricsService(metricsService)
                , m_viewConfirmedCallback(this, &MyPinCreationDetailsController::OnConfirmed)
                , m_viewDismissedCallback(this, &MyPinCreationDetailsController::OnDismissed)
                , m_viewModelOpenedCallback(this, &MyPinCreationDetailsController::OnOpened)
                , m_viewModelClosedCallback(this, &MyPinCreationDetailsController::OnClosed)
                , m_networkStateChangeCallback(this, &MyPinCreationDetailsController::OnNetworkStateChanged)
            {
                m_viewModel.InsertClosedCallback(m_viewModelClosedCallback);
                m_viewModel.InsertOpenedCallback(m_viewModelOpenedCallback);

                m_view.InsertConfirmedCallback(m_viewConfirmedCallback);
                m_view.InsertDismissedCallback(m_viewDismissedCallback);

                m_messageBus.SubscribeUi(m_networkStateChangeCallback);
            }

            MyPinCreationDetailsController::~MyPinCreationDetailsController()
            {
                m_messageBus.UnsubscribeUi(m_networkStateChangeCallback);

                m_viewModel.RemoveClosedCallback(m_viewModelClosedCallback);
                m_viewModel.RemoveOpenedCallback(m_viewModelOpenedCallback);

                m_view.RemoveConfirmedCallback(m_viewConfirmedCallback);
                m_view.RemoveDismissedCallback(m_viewDismissedCallback);
            }

            void MyPinCreationDetailsController::OnOpened()
            {
                if(m_viewModel.TryAcquireReactorControl())
                {
                    m_metricsService.BeginTimedEvent("MyPinCreationDetailsDialogue");
                    m_view.Open();
                }
            }

            void MyPinCreationDetailsController::OnClosed()
            {
                m_metricsService.EndTimedEvent("MyPinCreationDetailsDialogue");
                m_view.Close();
                
                ExampleApp::MyPinCreation::MyPinCreationViewStateChangedMessage message(ExampleApp::MyPinCreation::Inactive);
                m_messageBus.Publish(message);
            }

            void MyPinCreationDetailsController::OnConfirmed()
            {
                m_viewModel.Close();

                std::string title = m_view.GetTitle();
                std::string description = m_view.GetDescription();
                Byte* imageDataBytes = m_view.GetImageBuffer();
                size_t imageSize = m_view.GetImageSize();
                bool shouldShare = m_view.ShareSelected();

                ExampleApp::MyPinCreation::MyPinCreationViewSavePinMessage message(title,
                        description,
                        imageDataBytes,
                        imageSize,
                        shouldShare);

                m_messageBus.Publish(message);

                m_metricsService.SetEvent("MyPinCreationDetails: Confirmed",
                                          "Image", imageDataBytes ? "yes" : "no",
                                          "Shared", shouldShare ? "yes" : "no");
            }

            void MyPinCreationDetailsController::OnDismissed()
            {
                m_viewModel.Close();
            }

            void MyPinCreationDetailsController::OnNetworkStateChanged(const Net::ConnectivityChangedViewMessage& connectivityChangedMessage)
            {
                m_view.ConnectivityChanged(connectivityChangedMessage.IsConnected(), m_viewModel.IsOpen());
            }
        }
    }
}
