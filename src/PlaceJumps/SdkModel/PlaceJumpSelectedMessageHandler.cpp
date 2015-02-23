// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PlaceJumpSelectedMessageHandler.h"

namespace ExampleApp
{
    namespace PlaceJumps
    {
        namespace SdkModel
        {
            PlaceJumpSelectedMessageHandler::PlaceJumpSelectedMessageHandler(
                IPlaceJumpController& placeJumpController,
                ExampleAppMessaging::TMessageBus& messageBus)
                : m_placeJumpController(placeJumpController)
                , m_messageBus(messageBus)
                , m_handlerBinding(this, &PlaceJumpSelectedMessageHandler::OnPlaceJumpSelectedMessage)
            {
                m_messageBus.SubscribeNative(m_handlerBinding);
            }

            PlaceJumpSelectedMessageHandler::~PlaceJumpSelectedMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_handlerBinding);
            }

            void PlaceJumpSelectedMessageHandler::OnPlaceJumpSelectedMessage(const PlaceJumpSelectedMessage& message)
            {
                View::PlaceJumpModel model = message.Model();
                m_placeJumpController.JumpTo(model);
            }
        }
    }
}
