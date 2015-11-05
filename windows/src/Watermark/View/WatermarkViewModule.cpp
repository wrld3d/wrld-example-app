// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkViewModule.h"
#include "WindowsAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            WatermarkViewModule::WatermarkViewModule(
                WindowsNativeState& nativeState,
                IWatermarkViewModel& viewModel,
                ExampleAppMessaging::TMessageBus& messageBus,
                Metrics::IMetricsService& metricsService,
                const std::string& googleAnalyticsReferrerToken
            )
            {
                ASSERT_UI_THREAD

                m_pView = Eegeo_NEW(WatermarkView)(nativeState, googleAnalyticsReferrerToken);

                m_pController = Eegeo_NEW(WatermarkController)(
                                    viewModel,
                                    *m_pView,
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
