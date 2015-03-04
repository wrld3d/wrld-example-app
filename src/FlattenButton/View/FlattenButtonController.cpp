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
                ScreenControl::View::Apply(m_viewModel, m_view);
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
                , m_stateChangeHandler(this, &FlattenButtonController::OnFlattenButtonModelStateChangedMessage)
                , m_toggledCallback(this, &FlattenButtonController::OnToggleButton)
                , m_viewStateCallback(this, &FlattenButtonController::OnViewStateChangeScreenControl)
            {
                m_view.InsertToggleCallback(m_toggledCallback);
                m_viewModel.InsertOnScreenStateChangedCallback(m_viewStateCallback);
                m_messageBus.SubscribeUi(m_stateChangeHandler);
            }

            FlattenButtonController::~FlattenButtonController()
            {
                m_messageBus.UnsubscribeUi(m_stateChangeHandler);
                m_viewModel.RemoveOnScreenStateChangedCallback(m_viewStateCallback);
                m_view.RemoveToggleCallback(m_toggledCallback);
            }
        }
    }
}
