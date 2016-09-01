// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "Watermark.h"
#include "IWatermarkView.h"
#include "IWatermarkViewModel.h"
#include "ApplyScreenControl.h"
#include "MyPinCreationStateChangedMessage.h"
#include "IMetricsService.h"
#include "SetWatermarkVisibilityMessage.h"
#include "AppModes.h"
#include "WatermarkAlignmentStateChangedMessage.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            class WatermarkController : private Eegeo::NonCopyable
            {
            private:
                const std::shared_ptr<IWatermarkViewModel> m_viewModel;
                const std::shared_ptr<IWatermarkView> m_view;
                const std::shared_ptr<IWatermarkDataRepository> m_watermarkDataRepository;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                const std::shared_ptr<Metrics::IMetricsService> m_metricsService;
                
                bool m_appModeAllowsOpen;

                Eegeo::Helpers::TCallback0<WatermarkController> m_selectedCallback;
                Eegeo::Helpers::TCallback2<WatermarkController, ScreenControl::View::IScreenControlViewModel&, float> m_viewStateCallback;
                Eegeo::Helpers::TCallback1<WatermarkController, const SetWatermarkVisibilityMessage&> m_setVisibilityHandler;
                Eegeo::Helpers::TCallback1<WatermarkController, const WatermarkModelChangedMessage&> m_watermarkModelChangedHandler;
                Eegeo::Helpers::TCallback1<WatermarkController, const WatermarkAlignmentStateChangedMessage&> m_watermarkAlignmentStateChangedHandler;
                Eegeo::Helpers::TCallback1<WatermarkController, const AppModes::AppModeChangedMessage&> m_appModeChangedHandler;

                void OnSelected();

                void OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel& viewModel, float& state);
                
                void OnHandleSetVisibility(const SetWatermarkVisibilityMessage& message);
                void OnWatermarkModelChanged(const WatermarkModelChangedMessage& message);
                void OnWatermarkAlignmentStateChanged(const WatermarkAlignmentStateChangedMessage& message);
                
                void OnAppModeChanged(const AppModes::AppModeChangedMessage& message);

            public:
                WatermarkController(
                                    const std::shared_ptr<IWatermarkViewModel>& viewModel,
                                    const std::shared_ptr<IWatermarkView>& view,
                                    const std::shared_ptr<IWatermarkDataRepository>& watermarkDataRepository,
                                    const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                    const std::shared_ptr<Metrics::IMetricsService>& metricsService
                );

                ~WatermarkController();
            };
        }
    }
}
