// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonController.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            void FlattenButtonController::OnToggleButton(bool& toggle)
            {
                m_metricsService.SetEvent("UIItem: Flatten Button", "State", toggle ? "flattened" : "unflattened");
                m_messageBus.Publish(FlattenButtonViewStateChangedMessage(toggle));
            }

            void FlattenButtonController::OnFlattenButtonModelStateChangedMessage(const FlattenButtonModelStateChangedMessage& message)
            {
                m_view.SetToggled(message.IsFlattened());
            }

            void FlattenButtonController::OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel& viewModel, float& state)
            {
                if (state > 0.001f && !m_appModeAllowsOpen)
                {
                    return;
                }
                ScreenControl::View::Apply(m_viewModel, m_view);
            }
            
            void FlattenButtonController::OnMyPinCreationStateChangedMessage(const MyPinCreation::MyPinCreationStateChangedMessage& message)
            {
                switch (message.GetMyPinCreationStage())
                {
                    case MyPinCreation::Inactive:
                    {
                        m_viewModel.AddToScreen();
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
            
            void FlattenButtonController::OnAppModeChanged(const AppModes::AppModeChangedMessage& message)
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

            FlattenButtonController::FlattenButtonController(
                IFlattenButtonViewModel& viewModel,
                IFlattenButtonView& view,
                ExampleAppMessaging::TMessageBus& messageBus,
                Metrics::IMetricsService& metricsService)
                : m_viewModel(viewModel)
                , m_view(view)
                , m_messageBus(messageBus)
                , m_metricsService(metricsService)
                , m_appModeAllowsOpen(true)
                , m_stateChangeHandler(this, &FlattenButtonController::OnFlattenButtonModelStateChangedMessage)
                , m_toggledCallback(this, &FlattenButtonController::OnToggleButton)
                , m_viewStateCallback(this, &FlattenButtonController::OnViewStateChangeScreenControl)
                , m_myPinCreationStateChangedMessageHandler(this, &FlattenButtonController::OnMyPinCreationStateChangedMessage)
                , m_appModeChangedMessage(this, &FlattenButtonController::OnAppModeChanged)
            {
                m_view.InsertToggleCallback(m_toggledCallback);
                m_viewModel.InsertOnScreenStateChangedCallback(m_viewStateCallback);
                m_messageBus.SubscribeUi(m_stateChangeHandler);
                m_messageBus.SubscribeUi(m_myPinCreationStateChangedMessageHandler);
                m_messageBus.SubscribeUi(m_appModeChangedMessage);
            }

            FlattenButtonController::~FlattenButtonController()
            {
                m_messageBus.UnsubscribeUi(m_appModeChangedMessage);
                m_messageBus.UnsubscribeUi(m_myPinCreationStateChangedMessageHandler);
                m_messageBus.UnsubscribeUi(m_stateChangeHandler);
                m_viewModel.RemoveOnScreenStateChangedCallback(m_viewStateCallback);
                m_view.RemoveToggleCallback(m_toggledCallback);
            }
        }
    }
}
