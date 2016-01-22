// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinCreationDetailsViewModule.h"
#include "Types.h"
#include "AndroidNativeState.h"
#include "MyPinCreationDetails.h"
#include "MyPinCreation.h"
#include "MyPinCreationDetailsViewIncludes.h"
#include "BidirectionalBus.h"
#include "IConnectivityService.h"
#include "IMetricsService.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            class MyPinCreationDetailsViewModule : public IMyPinCreationDetailsViewModule, private Eegeo::NonCopyable
            {
            private:
                MyPinCreationDetailsView* m_pView;
                MyPinCreationDetailsController* m_pController;

            public:
                MyPinCreationDetailsViewModule(
                    AndroidNativeState& nativeState,
                    MyPinCreationDetails::View::IMyPinCreationDetailsViewModel& viewModel,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    Metrics::IMetricsService& metricsService
                );

                ~MyPinCreationDetailsViewModule();
            };
        }
    }
}
