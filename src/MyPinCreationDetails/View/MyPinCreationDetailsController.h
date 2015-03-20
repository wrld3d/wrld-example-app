// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "MyPinCreationDetails.h"
#include "BidirectionalBus.h"
#include "IConnectivityService.h"
#include "ICallback.h"
#include "IMetricsService.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            class MyPinCreationDetailsController : private Eegeo::NonCopyable
            {
            public:

                MyPinCreationDetailsController(
                    IMyPinCreationDetailsView& view,
                    IMyPinCreationDetailsViewModel& viewModel,
                    Eegeo::Web::IConnectivityService& connectivityService,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    Metrics::IMetricsService& metricsService
                );
                ~MyPinCreationDetailsController();

            private:

                void OnOpened();
                void OnClosed();

                void OnConfirmed();
                void OnDismissed();

                void OnNetworkStateChanged(const bool& hasConnectivity);

                IMyPinCreationDetailsView& m_view;
                IMyPinCreationDetailsViewModel& m_viewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Web::IConnectivityService& m_connectivityService;

                Eegeo::Helpers::TCallback0<MyPinCreationDetailsController> m_viewModelOpenedCallback;
                Eegeo::Helpers::TCallback0<MyPinCreationDetailsController> m_viewModelClosedCallback;

                Eegeo::Helpers::TCallback0<MyPinCreationDetailsController> m_viewConfirmedCallback;
                Eegeo::Helpers::TCallback0<MyPinCreationDetailsController> m_viewDismissedCallback;

                Eegeo::Helpers::TCallback1<MyPinCreationDetailsController, const bool&> m_networkStateChangeCallback;
                
                Metrics::IMetricsService& m_metricsService;
            };
        }
    }
}
