// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "MyPinCreation.h"
#include "MyPinCreationDetails.h"
#include "ICallback.h"
#include "IScreenControlViewModel.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationConfirmationController: private Eegeo::NonCopyable
            {
            public:

                MyPinCreationConfirmationController(IMyPinCreationConfirmationViewModel& viewModel,
                                                    IMyPinCreationConfirmationView& view,
                                                    MyPinCreationDetails::View::IMyPinCreationDetailsViewModel& detailsViewModel,
                                                    ExampleAppMessaging::TMessageBus& messageBus,
                                                    Metrics::IMetricsService& metricsService);
                
                ~MyPinCreationConfirmationController();

            private:

                void OnDismissed();
                void OnConfirmed();
                void OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel& viewModel, float& state);

                IMyPinCreationConfirmationViewModel& m_viewModel;
                IMyPinCreationConfirmationView& m_view;
                MyPinCreationDetails::View::IMyPinCreationDetailsViewModel& m_detailsViewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback2<MyPinCreationConfirmationController, ScreenControl::View::IScreenControlViewModel&, float> m_viewStateCallback;
                Eegeo::Helpers::TCallback0<MyPinCreationConfirmationController> m_dismissedCallback;
                Eegeo::Helpers::TCallback0<MyPinCreationConfirmationController> m_confirmedCallback;
                
                Metrics::IMetricsService& m_metricsService;
            };
        }
    }
}
