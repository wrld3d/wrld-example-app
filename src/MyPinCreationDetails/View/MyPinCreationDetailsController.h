// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "MyPinCreationDetails.h"
#include "BidirectionalBus.h"
#include "IConnectivityService.h"
#include "ICallback.h"
#include "IMetricsService.h"
#include "NetIncludes.h"

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
                                               const std::shared_ptr<IMyPinCreationDetailsView>& view,
                                               const std::shared_ptr<IMyPinCreationDetailsViewModel>& viewModel,
                                               const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                               const std::shared_ptr<Metrics::IMetricsService>& metricsService
                );
                ~MyPinCreationDetailsController();

            private:

                void OnOpened();
                void OnClosed();

                void OnConfirmed();
                void OnDismissed();

                void OnNetworkStateChanged(const Net::ConnectivityChangedViewMessage& connectivityChangedMessage);

                const std::shared_ptr<IMyPinCreationDetailsView> m_view;
                const std::shared_ptr<IMyPinCreationDetailsViewModel> m_viewModel;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;

                Eegeo::Helpers::TCallback0<MyPinCreationDetailsController> m_viewModelOpenedCallback;
                Eegeo::Helpers::TCallback0<MyPinCreationDetailsController> m_viewModelClosedCallback;

                Eegeo::Helpers::TCallback0<MyPinCreationDetailsController> m_viewConfirmedCallback;
                Eegeo::Helpers::TCallback0<MyPinCreationDetailsController> m_viewDismissedCallback;

                Eegeo::Helpers::TCallback1<MyPinCreationDetailsController, const Net::ConnectivityChangedViewMessage&> m_networkStateChangeCallback;
                
                const std::shared_ptr<Metrics::IMetricsService> m_metricsService;
            };
        }
    }
}
