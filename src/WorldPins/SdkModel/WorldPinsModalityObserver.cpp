// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinsModalityObserver.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            WorldPinsModalityObserver::WorldPinsModalityObserver(WorldPins::SdkModel::IWorldPinsScaleController& worldPinsScaleController,
                    ExampleAppMessaging::TMessageBus& messageBus)
                : m_worldPinsScaleController(worldPinsScaleController)
                , m_messageBus(messageBus)
                , m_handlerBinding(this, &WorldPinsModalityObserver::OnModalityChangedMessage)
            {
                m_messageBus.SubscribeNative(m_handlerBinding);
            }

            WorldPinsModalityObserver::~WorldPinsModalityObserver()
            {
                m_messageBus.UnsubscribeNative(m_handlerBinding);
            }

            void WorldPinsModalityObserver::OnModalityChangedMessage(const Modality::ModalityChangedMessage &message)
            {
                m_worldPinsScaleController.SetModality(message.Modality());
            }
        }
    }
}
