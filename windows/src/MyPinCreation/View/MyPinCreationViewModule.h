// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinCreationViewModule.h"
#include "Types.h"
#include "WindowsNativeState.h"
#include "MyPinCreation.h"
#include "MyPinCreationDetails.h"
#include "MyPinCreationViewIncludes.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"
#include "PersistentSettings.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationViewModule : public IMyPinCreationViewModule, private Eegeo::NonCopyable
            {
            private:
                MyPinCreationInitiationView* m_pInitiationView;
                MyPinCreationInitiationController* m_pInitiationController;

                MyPinCreationConfirmationView* m_pConfirmationView;
                MyPinCreationConfirmationController* m_pConfirmationController;

            public:
                MyPinCreationViewModule(
                    WindowsNativeState& nativeState,
                    IMyPinCreationInitiationViewModel& initiationViewModel,
                    IMyPinCreationConfirmationViewModel& confirmationViewModel,
                    MyPinCreationDetails::View::IMyPinCreationDetailsViewModel& detailsViewModel,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    Metrics::IMetricsService& metricsService,
                    bool isInKioskMode
                );

                ~MyPinCreationViewModule();

                IMyPinCreationInitiationView& GetMyPinCreationInitiationView();
            };
        }
    }
}
