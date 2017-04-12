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
                IWatermarkViewModel& m_viewModel;
                IWatermarkView& m_view;
                IWatermarkDataRepository& m_watermarkDataRepository;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                bool m_appModeAllowsOpen;

                Eegeo::Helpers::TCallback0<WatermarkController> m_selectedCallback;
                Eegeo::Helpers::TCallback2<WatermarkController, ScreenControl::View::IScreenControlViewModel&, float> m_viewStateCallback;
                Eegeo::Helpers::TCallback1<WatermarkController, const SetWatermarkVisibilityMessage&> m_setVisibilityHandler;
                Eegeo::Helpers::TCallback1<WatermarkController, const WatermarkModelChangedMessage&> m_watermarkModelChangedHandler;
                Eegeo::Helpers::TCallback1<WatermarkController, const WatermarkAlignmentStateChangedMessage&> m_watermarkAlignmentStateChangedHandler;
                Eegeo::Helpers::TCallback1<WatermarkController, const AppModes::AppModeChangedMessage&> m_appModeChangedHandler;
                Eegeo::Helpers::TCallback1<WatermarkController, const WatermarkInteriorStylingStateChangedMessage&> m_watermarkInteriorStylingStateChangedHandler;
                Metrics::IMetricsService& m_metricsService;

                void OnSelected();

                void OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel& viewModel, float& state);
                
                void OnHandleSetVisibility(const SetWatermarkVisibilityMessage& message);
                void OnWatermarkModelChanged(const WatermarkModelChangedMessage& message);
                void OnWatermarkAlignmentStateChanged(const WatermarkAlignmentStateChangedMessage& message);
                
                void OnAppModeChanged(const AppModes::AppModeChangedMessage& message);

                void OnInteriorStylingStateChanged(const WatermarkInteriorStylingStateChangedMessage& message);

            public:
                WatermarkController(
                    IWatermarkViewModel& viewModel,
                    IWatermarkView& view,
                    IWatermarkDataRepository& watermarkDataRepository,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    Metrics::IMetricsService& metricsService
                );

                ~WatermarkController();
            };
        }
    }
}
