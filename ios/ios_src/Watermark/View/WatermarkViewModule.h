// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"
#include "WatermarkViewIncludes.h"
#include "Rendering.h"
#include "Watermark.h"
#include "IWatermarkViewModule.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            class WatermarkViewModule: public IWatermarkViewModule, private Eegeo::NonCopyable
            {
            private:
                WatermarkController* m_pController;
                WatermarkView* m_pView;

            public:
                WatermarkViewModule(IWatermarkViewModel& viewModel,
                                    IWatermarkDataRepository& watermarkDataRepository,
                                    const Eegeo::Rendering::ScreenProperties& screenProperties,
                                    ExampleAppMessaging::TMessageBus& messageBus,
                                    Metrics::IMetricsService& metricsService);

                ~WatermarkViewModule();

                WatermarkController& GetWatermarkController() const;

                WatermarkView& GetWatermarkView() const;
            };
        }
    }
}
