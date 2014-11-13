// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PlaceJumpSelectedMessageHandler.h"

namespace ExampleApp
{
	namespace PlaceJumps
	{
		PlaceJumpSelectedMessageHandler::PlaceJumpSelectedMessageHandler(
			IPlaceJumpController& placeJumpController,
			ExampleAppMessaging::UiToNativeMessageBus& messageBus)
			: m_placeJumpController(placeJumpController)
			, m_messageBus(messageBus)
			, m_handlerBinding(this, &PlaceJumpSelectedMessageHandler::HandleReceivedPlaceJumpSelectedMessage)
		{
			m_messageBus.Subscribe(m_handlerBinding);
		}

		PlaceJumpSelectedMessageHandler::~PlaceJumpSelectedMessageHandler()
		{
			m_messageBus.Unsubscribe(m_handlerBinding);
		}

		void PlaceJumpSelectedMessageHandler::HandleReceivedPlaceJumpSelectedMessage(const PlaceJumpSelectedMessage& message)
		{
			PlaceJumpModel model = message.Model();
			m_placeJumpController.JumpTo(model);
		}
	}
}
