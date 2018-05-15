// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "NavWidgetViewIncludes.h"
#include "INavWidgetViewModule.h"
#include "NavWidgetController.h"
#include "NavWidgetViewModel.h"
#include "ILocationService.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            class NavWidgetViewModule: public INavWidgetViewModule, private Eegeo::NonCopyable
            {
            private:
                NavWidgetView* m_pView;
                NavWidgetController* m_pController;

            public:
                NavWidgetViewModule(
                    AndroidNativeState& nativeState,
                    INavWidgetViewModel& navWidgetViewModel,
                    ExampleAppMessaging::TMessageBus& messageBus
                );

                ~NavWidgetViewModule();

                NavWidgetView& GetView() const;
                NavWidgetController& GetController() const;
            };
        }
    }
}
