// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "MyPinCreationInitiationViewIncludes.h"
#include "Rendering.h"
#include "MyPinCreation.h"
#include "IMyPinCreationInitiationViewModule.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"
#include "IAppModeModel.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationInitiationViewModule: public IMyPinCreationInitiationViewModule, private Eegeo::NonCopyable
            {
            private:
                MyPinCreationInitiationController* m_pController;
                MyPinCreationInitiationView* m_pView;


            public:
                MyPinCreationInitiationViewModule(ExampleAppMessaging::TMessageBus& messageBus,
                                                  IMyPinCreationInitiationViewModel& viewModel,
                                                  IMyPinCreationConfirmationViewModel& confirmationViewModel,
                                                  const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                  Metrics::IMetricsService& metricsService);

                ~MyPinCreationInitiationViewModule();

                MyPinCreationInitiationController& GetMyPinCreationInitiationController() const;

                MyPinCreationInitiationView& GetMyPinCreationInitiationView() const;
            };
        }
    }
}
