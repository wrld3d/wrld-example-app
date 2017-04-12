// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkViewModule.h"
#include "WatermarkView.h"
#include "ScreenProperties.h"
#include "WatermarkController.h"
#include "WatermarkViewInterop.h"
#include "IWatermarkDataRepository.h"
#include "WatermarkData.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            WatermarkViewModule::WatermarkViewModule(IWatermarkViewModel& viewModel,
                                                     IWatermarkDataRepository& watermarkDataRepository,
                                                     const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                     ExampleAppMessaging::TMessageBus& messageBus,
                                                     Metrics::IMetricsService& metricsService)
            {
                WatermarkData defaultWatermarkData = watermarkDataRepository.GetWatermarkDataWithKey("eegeo");
                m_pView = [[WatermarkView alloc] initWithScreenDimensions
                           :screenProperties.GetScreenWidth()
                           :screenProperties.GetScreenHeight()
                           :screenProperties.GetPixelScale()
                           :defaultWatermarkData
                          ];

                m_pController = new WatermarkController(viewModel, *[m_pView getInterop], watermarkDataRepository, messageBus, metricsService);
            }

            WatermarkViewModule::~WatermarkViewModule()
            {
                delete m_pController;
                [m_pView release];
            }

            WatermarkController& WatermarkViewModule::GetWatermarkController() const
            {
                return *m_pController;
            }

            WatermarkView& WatermarkViewModule::GetWatermarkView() const
            {
                return *m_pView;
            }
        }
    }
}
