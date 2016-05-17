// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkViewModule.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "IWatermarkDataRepository.h"
#include "WatermarkData.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            WatermarkViewModule::WatermarkViewModule(
                AndroidNativeState& nativeState,
                IWatermarkViewModel& viewModel,
				IWatermarkDataRepository& watermarkDataRepository,
                ExampleAppMessaging::TMessageBus& messageBus,
                Metrics::IMetricsService& metricsService
            )
            {
                ASSERT_UI_THREAD

				const WatermarkData& defaultWatermarkData = watermarkDataRepository.GetWatermarkDataWithKey("eegeo");
                m_pView = Eegeo_NEW(WatermarkView)(nativeState, defaultWatermarkData);

                m_pController = Eegeo_NEW(WatermarkController)(
                                    viewModel,
                                    *m_pView,
									watermarkDataRepository,
                                    messageBus,
                                    metricsService);

            }

            WatermarkViewModule::~WatermarkViewModule()
            {
                ASSERT_UI_THREAD
                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pView;
            }
        }
    }
}
