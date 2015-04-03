// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkController.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            void WatermarkController::OnSelected()
            {
                m_metricsService.SetEvent("UIItem: Watermark Selected");
            }

            void WatermarkController::OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel& viewModel, float& state)
            {
                ScreenControl::View::Apply(m_viewModel, m_view);
            }
            
            void WatermarkController::OnHandleSetVisibility(const SetWatermarkVisibilityMessage& message)
            {
                if(message.GetShouldSetVisible())
                {
                    m_viewModel.AddToScreen();
                }
                else
                {
                    m_viewModel.RemoveFromScreen();
                }
            }
            
            WatermarkController::WatermarkController(
                IWatermarkViewModel& viewModel,
                IWatermarkView& view,
                ExampleAppMessaging::TMessageBus& messageBus,
                Metrics::IMetricsService& metricsService
            )
                : m_viewModel(viewModel)
                , m_view(view)
                , m_messageBus(messageBus)
                , m_metricsService(metricsService)
                , m_selectedCallback(this, &WatermarkController::OnSelected)
                , m_viewStateCallback(this, &WatermarkController::OnViewStateChangeScreenControl)
                , m_setVisibilityHandler(this, &WatermarkController::OnHandleSetVisibility)
            {
                m_view.InsertSelectedCallback(m_selectedCallback);
                m_viewModel.InsertOnScreenStateChangedCallback(m_viewStateCallback);
                m_messageBus.SubscribeUi(m_setVisibilityHandler);
            }

            WatermarkController::~WatermarkController()
            {
                m_messageBus.UnsubscribeUi(m_setVisibilityHandler);
                m_viewModel.RemoveOnScreenStateChangedCallback(m_viewStateCallback);
                m_view.RemoveSelectedCallback(m_selectedCallback);
            }
        }
    }
}
