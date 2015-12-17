// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "FlattenButtonViewIncludes.h"
#include "Rendering.h"
#include "FlattenButton.h"
#include "IFlattenButtonViewModule.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"
#include "IAppModeModel.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            class FlattenButtonViewModule: public IFlattenButtonViewModule, private Eegeo::NonCopyable
            {
            private:
                FlattenButtonController* m_pController;
                FlattenButtonView* m_pView;

            public:
                FlattenButtonViewModule(IFlattenButtonViewModel& viewModel,
                                        const Eegeo::Rendering::ScreenProperties& screenProperties,
                                        ExampleAppMessaging::TMessageBus& messageBus,
                                        Metrics::IMetricsService& metricsService);

                ~FlattenButtonViewModule();

                FlattenButtonController& GetFlattenButtonController() const;

                FlattenButtonView& GetFlattenButtonView() const;
            };
        }
    }
}
