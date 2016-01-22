// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinCreationDetailsViewModule.h"
#include "MyPinCreationDetailsViewIncludes.h"
#include "MyPinCreationDetails.h"
#include "MyPinCreation.h"
#include "BidirectionalBus.h"
#include "Rendering.h"
#include "IConnectivityService.h"
#include "IMetricsService.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            class MyPinCreationDetailsViewModule : public IMyPinCreationDetailsViewModule
            {
            public:
                MyPinCreationDetailsViewModule(ExampleAppMessaging::TMessageBus& messageBus,
                                               IMyPinCreationDetailsViewModel& myPinCreationDetailsViewModel,
                                               const Eegeo::Rendering::ScreenProperties& screenProperties,
                                               Metrics::IMetricsService& metricsService,
                                               UIViewController* rootViewController);

                ~MyPinCreationDetailsViewModule();

                MyPinCreationDetailsController& GetMyPinCreationDetailsController() const;
                MyPinCreationDetailsView& GetMyPinCreationDetailsView() const;

            private:
                MyPinCreationDetailsView* m_pView;
                MyPinCreationDetailsController* m_pController;
            };
        }
    }
}
