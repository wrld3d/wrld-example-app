// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#import "FlattenButtonViewModule.h"
#include "RenderContext.h"
#include "FlattenButtonView.h"
#include "ScreenProperties.h"
#include "FlattenButtonController.h"
#include "FlattenButtonViewInterop.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            FlattenButtonViewModule::FlattenButtonViewModule(IFlattenButtonViewModel& viewModel,
                                                                const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                             ExampleAppMessaging::TMessageBus& messageBus,
                                                             Metrics::IMetricsService& metricsService)
            {
                m_pView = [[FlattenButtonView alloc] initWithDimensions
                           :screenProperties.GetScreenWidth()
                           :screenProperties.GetScreenHeight()
                           :screenProperties.GetPixelScale()
                          ];

                m_pController = new FlattenButtonController(viewModel, *[m_pView getInterop], messageBus, metricsService);
            }

            FlattenButtonViewModule::~FlattenButtonViewModule()
            {
                delete m_pController;
                [m_pView release];
            }

            FlattenButtonController& FlattenButtonViewModule::GetFlattenButtonController() const
            {
                return *m_pController;
            }

            FlattenButtonView& FlattenButtonViewModule::GetFlattenButtonView() const
            {
                return *m_pView;
            }
        }
    }
}
