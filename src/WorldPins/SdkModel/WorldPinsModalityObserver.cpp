// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WorldPinsModalityObserver.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        WorldPinsModalityObserver::WorldPinsModalityObserver(WorldPins::IWorldPinsScaleController& worldPinsScaleController,
                                                             ExampleAppMessaging::UiToNativeMessageBus& messageBus)
        : m_worldPinsScaleController(worldPinsScaleController)
        , m_messageBus(messageBus)
        , m_handlerBinding(this, &WorldPinsModalityObserver::HandleReceivedModalityChangedMessage)
        {
            m_messageBus.Subscribe(m_handlerBinding);
        }
        
        WorldPinsModalityObserver::~WorldPinsModalityObserver()
        {
            m_messageBus.Unsubscribe(m_handlerBinding);
        }
        
        void WorldPinsModalityObserver::HandleReceivedModalityChangedMessage(const Modality::ModalityChangedMessage &message)
        {
            m_worldPinsScaleController.SetModality(message.Modality());
        }
    }
}