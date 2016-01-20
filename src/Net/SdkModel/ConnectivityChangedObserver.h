// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Web.h"
#include "ICallback.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace Net
    {
        namespace SdkModel
        {
            class ConnectivityChangedObserver
            {
            public:
                
                ConnectivityChangedObserver(Eegeo::Web::WebConnectivityValidator& connectivityValidator,
                                            ExampleAppMessaging::TMessageBus& messageBus);
                ~ConnectivityChangedObserver();
                
            private:
                
                Eegeo::Helpers::TCallback0<ConnectivityChangedObserver> m_connectivityChangeCallback;
                
                void HandleConnectivityChanged();
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Web::WebConnectivityValidator& m_connectivityValidator;
            };
        }
    }
}