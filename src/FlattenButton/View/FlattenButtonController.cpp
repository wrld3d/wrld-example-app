// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonController.h"
#include "VirtualKeyboardStateChangedMessage.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            void FlattenButtonController::OnToggleButton(bool& toggle)
            {
                if (!m_appModeAllowsOpen)
                {
                    m_view.SetToggled(false);
                    return;
                }
                
                m_metricsService.SetEvent("UIItem: Flatten Button", "State", toggle ? "flattened" : "unflattened");
                m_messageBus.Publish(FlattenButtonViewStateChangedMessage(toggle));
            }

            void FlattenButtonController::OnFlattenButtonModelStateChangedMessage(const FlattenButtonModelStateChangedMessage& message)
            {
                m_view.SetToggled(message.IsFlattened());
            }

            void FlattenButtonController::OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel& viewModel, float& state)
            {
                ScreenControl::View::Apply(m_viewModel, m_view);
            }
            
            void FlattenButtonController::OnMyPinCreationStateChangedMessage(const MyPinCreation::MyPinCreationStateChangedMessage& message)
            {
                switch (message.GetMyPinCreationStage())
                {
                    case MyPinCreation::Inactive:
                    {
                        if (m_appModeAllowsOpen)
                        {
                            m_viewModel.AddToScreen();
                        }
                    }break;
                    case MyPinCreation::Ring:
                    {
                        m_viewModel.RemoveFromScreen();
                    }break;
                    case MyPinCreation::Details:
                    {
                    }break;
                    default:
                    {
                        Eegeo_ASSERT(false, "Unknown MyPinCreationStage");
                    }
                }
            }
            
            void FlattenButtonController::OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message)
            {
                m_appModeAllowsOpen = message.GetAppMode() != AppModes::SdkModel::AttractMode;
                
                if(m_appModeAllowsOpen)
                {
                    m_viewModel.AddToScreen();
                    if(message.GetAppMode() == AppModes::SdkModel::InteriorMode)
                    {
                        m_view.SetViewEnabled(false);
                    }
                    else
                    {
                        m_view.SetViewEnabled(true);
                    }
                }
                else
                {
                    m_viewModel.RemoveFromScreen();
                }
            }

            void FlattenButtonController::OnVirtualKeyboardStateChangedMessage(const VirtualKeyboard::VirtualKeyboardStateChangedMessage& message)
            {
                if (m_appModeAllowsOpen)
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
            }

            FlattenButtonController::FlattenButtonController(
                IFlattenButtonViewModel& viewModel,
                IFlattenButtonView& view,
                ExampleAppMessaging::TMessageBus& messageBus,
                Metrics::IMetricsService& metricsService
            )

                : m_viewModel(viewModel)
                , m_view(view)
                , m_messageBus(messageBus)
                , m_metricsService(metricsService)
                , m_appModeAllowsOpen(true)
                , m_stateChangeHandler(this, &FlattenButtonController::OnFlattenButtonModelStateChangedMessage)
                , m_toggledCallback(this, &FlattenButtonController::OnToggleButton)
                , m_viewStateCallback(this, &FlattenButtonController::OnViewStateChangeScreenControl)
                , m_myPinCreationStateChangedMessageHandler(this, &FlattenButtonController::OnMyPinCreationStateChangedMessage)
                , m_appModeChangedHandler(this, &FlattenButtonController::OnAppModeChangedMessage)
                , m_virtualKeyboardStateChangedMessageHandler(this, &FlattenButtonController::OnVirtualKeyboardStateChangedMessage)
            {
                m_view.InsertToggleCallback(m_toggledCallback);
                m_viewModel.InsertOnScreenStateChangedCallback(m_viewStateCallback);
                m_messageBus.SubscribeUi(m_stateChangeHandler);
                m_messageBus.SubscribeUi(m_myPinCreationStateChangedMessageHandler);
                m_messageBus.SubscribeUi(m_appModeChangedHandler);
                m_messageBus.SubscribeUi(m_virtualKeyboardStateChangedMessageHandler);
            }

            FlattenButtonController::~FlattenButtonController()
            {
                m_messageBus.UnsubscribeUi(m_virtualKeyboardStateChangedMessageHandler);
                m_messageBus.UnsubscribeUi(m_appModeChangedHandler);
                m_messageBus.UnsubscribeUi(m_myPinCreationStateChangedMessageHandler);
                m_messageBus.UnsubscribeUi(m_stateChangeHandler);
                m_viewModel.RemoveOnScreenStateChangedCallback(m_viewStateCallback);
                m_view.RemoveToggleCallback(m_toggledCallback);
            }
        }
    }
}
