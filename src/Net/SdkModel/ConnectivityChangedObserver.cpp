// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ConnectivityChangedObserver.h"
#include "WebConnectivityValidator.h"
#include "ConnectivityChangedViewMessage.h"

namespace ExampleApp
{
    namespace Net
    {
        namespace SdkModel
        {
            ConnectivityChangedObserver::ConnectivityChangedObserver(Eegeo::Web::WebConnectivityValidator& connectivityValidator,
                                                                     ExampleAppMessaging::TMessageBus& messageBus)
            : m_connectivityValidator(connectivityValidator)
            , m_messageBus(messageBus)
            , m_connectivityChangeCallback(this, &ConnectivityChangedObserver::HandleConnectivityChanged)
            {
                m_connectivityValidator.RegisterStateChangedCallback(m_connectivityChangeCallback);
            }
            
            ConnectivityChangedObserver::~ConnectivityChangedObserver()
            {
                m_connectivityValidator.UnregisterStateChangedCallback(m_connectivityChangeCallback);
            }
            
            void ConnectivityChangedObserver::HandleConnectivityChanged()
            {
                m_messageBus.Publish(ConnectivityChangedViewMessage(m_connectivityValidator.IsValid()));
            }
        }
    }
}