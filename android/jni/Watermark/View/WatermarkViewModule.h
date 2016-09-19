// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

//#include <string>
//#include "IWatermarkViewModule.h"
//#include "AndroidNativeState.h"
//#include "Types.h"
//#include "Watermark.h"
//#include "WatermarkViewIncludes.h"
//#include "WatermarkView.h"
//#include "WatermarkController.h"
//#include "IMetricsService.h"
#include "Module.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            class WatermarkViewModule: public Module
            {
            public:
            	void Register(const TContainerBuilder& builder);
//            private:
//                WatermarkView* m_pView;
//                WatermarkController* m_pController;
//
//            public:
//                WatermarkViewModule(
//                    AndroidNativeState& nativeState,
//                    IWatermarkViewModel& viewModel,
//					IWatermarkDataRepository& watermarkDataRepository,
//                    ExampleAppMessaging::TMessageBus& messageBus,
//                    Metrics::IMetricsService& metricsService
//                );
//
//                ~WatermarkViewModule();
            };
        }
    }
}
