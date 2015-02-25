// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationDetailsController.h"
#include "IMyPinCreationDetailsView.h"
#include "IMyPinCreationDetailsViewModel.h"
#include "MyPinCreationViewStateChangedMessage.h"
#include "MyPinCreationViewSavePinMessage.h"
#include "FlurryWrapper.h"
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
                Eegeo::Web::IConnectivityService& connectivityService,
                ExampleAppMessaging::TMessageBus& messageBus
            )
                : m_view(view)
                , m_viewModel(viewModel)
                , m_messageBus(messageBus)
                , m_connectivityService(connectivityService)
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

                m_connectivityService.RegisterConnectivityChangedCallback(m_networkStateChangeCallback);

                OnNetworkStateChanged(m_connectivityService.HasConnectivity());
            }

            MyPinCreationDetailsController::~MyPinCreationDetailsController()
            {
                m_connectivityService.UnregisterConnectivityChangedCallback(m_networkStateChangeCallback);

                m_viewModel.RemoveClosedCallback(m_viewModelClosedCallback);
                m_viewModel.RemoveOpenedCallback(m_viewModelOpenedCallback);

                m_view.RemoveConfirmedCallback(m_viewConfirmedCallback);
                m_view.RemoveDismissedCallback(m_viewDismissedCallback);
            }

            void MyPinCreationDetailsController::OnOpened()
            {
                if(m_viewModel.TryAcquireReactorControl())
                {
                    FLURRY_BEGIN_TIMED_EVENT("MyPinCreationDetailsDialogue");
                    m_view.Open();
                }
            }

            void MyPinCreationDetailsController::OnClosed()
            {
                FLURRY_END_TIMED_EVENT("MyPinCreationDetailsDialogue");
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

                FLURRY_SET_EVENT("MyPinCreationDetails: Confirmed",
                				 "Image", imageDataBytes ? "yes" : "no",
                				 "Shared", shouldShare ? "yes" : "no");
            }

            void MyPinCreationDetailsController::OnDismissed()
            {
                m_viewModel.Close();
            }

            void MyPinCreationDetailsController::OnNetworkStateChanged(const bool &hasConnectivity)
            {
                m_view.ConnectivityChanged(hasConnectivity, m_viewModel.IsOpen());
            }
        }
    }
}
