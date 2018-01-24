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

                void OnOpened();
                void OnDismissed();
                void OnConfirmed();
                void OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel& viewModel);

                IMyPinCreationConfirmationViewModel& m_viewModel;
                IMyPinCreationConfirmationView& m_view;
                MyPinCreationDetails::View::IMyPinCreationDetailsViewModel& m_detailsViewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Metrics::IMetricsService& m_metricsService;
                bool m_appModeAllowsOpen;
                bool m_userInteractionEnabled;

                Eegeo::Helpers::TCallback1<MyPinCreationConfirmationController, ScreenControl::View::IScreenControlViewModel&> m_viewStateCallback;
                Eegeo::Helpers::TCallback0<MyPinCreationConfirmationController> m_dismissedCallback;
                Eegeo::Helpers::TCallback0<MyPinCreationConfirmationController> m_confirmedCallback;
                Eegeo::Helpers::TCallback0<MyPinCreationConfirmationController> m_openedCallback;
            };
        }
    }
}
