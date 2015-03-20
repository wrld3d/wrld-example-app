// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "MyPinCreationConfirmationViewIncludes.h"
#include "Rendering.h"
#include "MyPinCreation.h"
#include "IMyPinCreationConfirmationViewModule.h"
#include "MyPinCreationDetails.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationConfirmationViewModule: public IMyPinCreationConfirmationViewModule, private Eegeo::NonCopyable
            {
            private:
                MyPinCreationConfirmationController* m_pController;
                MyPinCreationConfirmationView* m_pView;

            public:
                MyPinCreationConfirmationViewModule(ExampleAppMessaging::TMessageBus& messageBus,
                                                    IMyPinCreationConfirmationViewModel& viewModel,
                                                    IMyPinCreationCompositeViewModel& compositeViewModel,
                                                    MyPinCreationDetails::View::IMyPinCreationDetailsViewModel& detailsViewModel,
                                                    const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                    Metrics::IMetricsService& metricsService);

                ~MyPinCreationConfirmationViewModule();

                MyPinCreationConfirmationController& GetMyPinCreationConfirmationController() const;

                MyPinCreationConfirmationView& GetMyPinCreationConfirmationView() const;
            };
        }
    }
}
