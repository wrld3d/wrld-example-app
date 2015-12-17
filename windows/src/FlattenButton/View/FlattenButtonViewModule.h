// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IFlattenButtonViewModule.h"
#include "WindowsNativeState.h"
#include "Types.h"
#include "FLattenButton.h"
#include "FlattenButtonViewIncludes.h"
#include "FlattenButtonView.h"
#include "FlattenButtonController.h"
#include "IMetricsService.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            class FlattenButtonViewModule: public IFlattenButtonViewModule, private Eegeo::NonCopyable
            {
            private:
                FlattenButtonView* m_pView;
                FlattenButtonController* m_pController;

            public:
                FlattenButtonViewModule(
                    WindowsNativeState& nativeState,
                    IFlattenButtonViewModel& viewModel,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    Metrics::IMetricsService& metricsService
                );

                ~FlattenButtonViewModule();
            };
        }
    }
}
