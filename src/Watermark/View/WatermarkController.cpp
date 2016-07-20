// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkController.h"
#include "IAppModeModel.h"
#include "IWatermarkDataRepository.h"
#include "WatermarkData.h"

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
                if(!m_appModeAllowsOpen && state > 0.01f)
                {
                    return;
                }
                
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
            
            void WatermarkController::OnWatermarkModelChanged(const ExampleApp::Watermark::WatermarkModelChangedMessage& message)
            {
                if (m_watermarkDataRepository.HasWatermarkDataForKey(message.GetWatermarkId()))
                {
                    const WatermarkData& watermarkDataForVendor = m_watermarkDataRepository.GetWatermarkDataWithKey(message.GetWatermarkId());
                    m_view.UpdateWatermarkData(watermarkDataForVendor);
                }
            }
            
            
            void WatermarkController::OnWatermarkAlignmentStateChanged(const WatermarkAlignmentStateChangedMessage& message)
            {
                m_view.SetWatermarkAlignmentState(message.ShouldAlignBottom(), message.ShouldAlignBelowFloorDisplay());
            }
            
            void WatermarkController::OnAppModeChanged(const AppModes::AppModeChangedMessage& message)
            {
                const AppModes::SdkModel::AppMode appMode = message.GetAppMode();
                m_appModeAllowsOpen = appMode == AppModes::SdkModel::WorldMode ||
                                      appMode == AppModes::SdkModel::InteriorMode;
                
                if(m_appModeAllowsOpen && !m_viewModel.IsFullyOnScreen())
                {
                    m_viewModel.AddToScreen();
                }
                else if(!m_appModeAllowsOpen && !m_viewModel.IsFullyOffScreen())
                {
                    m_viewModel.RemoveFromScreen();
                }
            }
            
            WatermarkController::WatermarkController(
                IWatermarkViewModel& viewModel,
                IWatermarkView& view,
                IWatermarkDataRepository& watermarkDataRepository,
                ExampleAppMessaging::TMessageBus& messageBus,
                Metrics::IMetricsService& metricsService
            )
                : m_viewModel(viewModel)
                , m_view(view)
                , m_watermarkDataRepository(watermarkDataRepository)
                , m_messageBus(messageBus)
                , m_metricsService(metricsService)
                , m_selectedCallback(this, &WatermarkController::OnSelected)
                , m_viewStateCallback(this, &WatermarkController::OnViewStateChangeScreenControl)
                , m_setVisibilityHandler(this, &WatermarkController::OnHandleSetVisibility)
                , m_watermarkModelChangedHandler(this, &WatermarkController::OnWatermarkModelChanged)
                , m_watermarkAlignmentStateChangedHandler(this, &WatermarkController::OnWatermarkAlignmentStateChanged)
                , m_appModeChangedHandler(this, &WatermarkController::OnAppModeChanged)
                , m_appModeAllowsOpen(true)
            {
                m_view.InsertSelectedCallback(m_selectedCallback);
                m_viewModel.InsertOnScreenStateChangedCallback(m_viewStateCallback);
                m_messageBus.SubscribeUi(m_setVisibilityHandler);
                m_messageBus.SubscribeUi(m_watermarkModelChangedHandler);
                m_messageBus.SubscribeUi(m_watermarkAlignmentStateChangedHandler);
                m_messageBus.SubscribeUi(m_appModeChangedHandler);
            }

            WatermarkController::~WatermarkController()
            {
                m_messageBus.UnsubscribeUi(m_setVisibilityHandler);
                m_messageBus.UnsubscribeUi(m_watermarkAlignmentStateChangedHandler);
                m_messageBus.UnsubscribeUi(m_watermarkModelChangedHandler);
                m_messageBus.UnsubscribeUi(m_appModeChangedHandler);
                m_viewModel.RemoveOnScreenStateChangedCallback(m_viewStateCallback);
                m_view.RemoveSelectedCallback(m_selectedCallback);
            }
        }
    }
}
