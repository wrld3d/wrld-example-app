// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PlaceJumpSelectedMessageHandler.h"

namespace ExampleApp
{
	namespace PlaceJumps
	{
		PlaceJumpSelectedMessageHandler::PlaceJumpSelectedMessageHandler(
			IPlaceJumpController& placeJumpController,
			ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
			: m_placeJumpController(placeJumpController)
			, m_uiToNativeMessageBus(uiToNativeMessageBus)
			, m_handlerBinding(this, &PlaceJumpSelectedMessageHandler::HandleReceivedPlaceJumpSelectedMessage)
		{
			m_uiToNativeMessageBus.Subscribe(m_handlerBinding);
		}

		PlaceJumpSelectedMessageHandler::~PlaceJumpSelectedMessageHandler()
		{
			m_uiToNativeMessageBus.Unsubscribe(m_handlerBinding);
		}

		void PlaceJumpSelectedMessageHandler::HandleReceivedPlaceJumpSelectedMessage(const PlaceJumpSelectedMessage& message)
		{
			PlaceJumpModel model = message.Model();
			m_placeJumpController.JumpTo(model);
		}
	}
}
