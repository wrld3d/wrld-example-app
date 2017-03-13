// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsController.h"
#include "IMyPinDetailsView.h"
#include "IMyPinDetailsViewModel.h"
#include "MyPinDetailsViewRemovePinMessage.h"
#include "MyPinModel.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            MyPinDetailsController::MyPinDetailsController(
                IMyPinDetailsView& view,
                IMyPinDetailsViewModel& viewModel,
                ExampleAppMessaging::TMessageBus& messageBus)
                : m_view(view)
                , m_viewModel(viewModel)
                , m_messageBus(messageBus)
                , m_viewModelOpenedCallback(this, &MyPinDetailsController::OnOpened)
                , m_viewModelClosedCallback(this, &MyPinDetailsController::OnClosed)
                , m_viewDismissedCallback(this, &MyPinDetailsController::OnDismissed)
                , m_viewRemovePinCallback(this, &MyPinDetailsController::OnRemovePin)
                , m_appModeChangedHandler(this, &MyPinDetailsController::OnAppModeChangedMessage)
            {
                m_viewModel.InsertOpenedCallback(m_viewModelOpenedCallback);
                m_viewModel.InsertClosedCallback(m_viewModelClosedCallback);

                m_view.InsertDismissedCallback(m_viewDismissedCallback);
                m_view.InsertRemovePinCallback(m_viewRemovePinCallback);

                m_messageBus.SubscribeUi(m_appModeChangedHandler);
            }

            MyPinDetailsController::~MyPinDetailsController()
            {
                m_messageBus.UnsubscribeUi(m_appModeChangedHandler);

                m_view.RemoveDismissedCallback(m_viewDismissedCallback);
                m_view.RemoveRemovePinCallback(m_viewRemovePinCallback);

                m_viewModel.RemoveClosedCallback(m_viewModelClosedCallback);
                m_viewModel.RemoveOpenedCallback(m_viewModelOpenedCallback);
            }

            void MyPinDetailsController::OnOpened()
            {
                if(m_viewModel.TryAcquireReactorControl())
                {
                    m_view.OpenWithModel(m_viewModel.GetMyPinTitle(),
                                         m_viewModel.GetMyPinDescription(),
                                         m_viewModel.GetImagePath());
                }
                else
                {
                    m_view.Close();
                }
            }

            void MyPinDetailsController::OnClosed()
            {
                m_view.Close();
            }

            void MyPinDetailsController::OnDismissed()
            {
                m_viewModel.Close();
            }

            void MyPinDetailsController::OnRemovePin()
            {
                if(m_viewModel.IsOpen())
                {
                    ExampleApp::MyPinDetails::MyPinDetailsViewRemovePinMessage message(m_viewModel.GetMyPinId());
                    m_messageBus.Publish(message);

                    m_viewModel.Close();
                }
            }

            void MyPinDetailsController::OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message)
            {
                const bool appModeAllowsOpen = message.GetAppMode() != AppModes::SdkModel::AttractMode;

                if (!appModeAllowsOpen)
                {
                    if (m_viewModel.IsOpen())
                    {
                        m_viewModel.Close();
                    }
                }
            }
        }
    }

}
