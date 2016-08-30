// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Web.h"
#include "ICallback.h"
#include "BidirectionalBus.h"

#include <memory>

namespace ExampleApp
{
    namespace Net
    {
        namespace SdkModel
        {
            class ConnectivityChangedObserver
            {
            public:
                
                ConnectivityChangedObserver(const std::shared_ptr<Eegeo::Web::WebConnectivityValidator>& connectivityValidator,
                                            const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);
                ~ConnectivityChangedObserver();
                
            private:
                
                Eegeo::Helpers::TCallback0<ConnectivityChangedObserver> m_connectivityChangeCallback;
                
                void HandleConnectivityChanged();
                
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                const std::shared_ptr<Eegeo::Web::WebConnectivityValidator> m_connectivityValidator;
            };
        }
    }
}