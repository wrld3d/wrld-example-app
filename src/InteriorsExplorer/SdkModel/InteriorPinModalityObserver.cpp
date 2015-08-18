// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorPinModalityObserver.h"
#include "InteriorPinsSetScaleMessage.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorPinModalityObserver::InteriorPinModalityObserver(ExampleAppMessaging::TMessageBus& messageBus)
            : m_messageBus(messageBus)
            , m_handlerBinding(this, &InteriorPinModalityObserver::OnModalityChangedMessage)
            {
                m_messageBus.SubscribeNative(m_handlerBinding);
            }
            
            InteriorPinModalityObserver::~InteriorPinModalityObserver()
            {
                m_messageBus.UnsubscribeNative(m_handlerBinding);
            }
                
            void InteriorPinModalityObserver::OnModalityChangedMessage(const Modality::ModalityChangedMessage& message)
            {
                m_messageBus.Publish(InteriorPinsSetScaleMessage(1.f - message.Modality()));
            }
        }
    }
}