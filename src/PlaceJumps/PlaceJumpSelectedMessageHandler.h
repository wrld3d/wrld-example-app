// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "UiToNativeMessageBus.h"
#include "IPlaceJumpController.h"
#include "ICallback.h"
#include "PlaceJumpSelectedMessage.h"

namespace ExampleApp
{
	namespace PlaceJumps
	{
		class PlaceJumpSelectedMessageHandler : private Eegeo::NonCopyable
		{
			IPlaceJumpController& m_placeJumpController;
			ExampleAppMessaging::UiToNativeMessageBus& m_messageBus;
			Eegeo::Helpers::TCallback1<PlaceJumpSelectedMessageHandler, const PlaceJumpSelectedMessage&> m_handlerBinding;

			void HandleReceivedPlaceJumpSelectedMessage(const PlaceJumpSelectedMessage& message)
			{
                PlaceJumpModel model = message.Model();
				m_placeJumpController.JumpTo(model);
			}

		public:
			PlaceJumpSelectedMessageHandler(
				IPlaceJumpController& placeJumpController,
				ExampleAppMessaging::UiToNativeMessageBus& messageBus)
			: m_placeJumpController(placeJumpController)
			, m_messageBus(messageBus)
			, m_handlerBinding(this, &PlaceJumpSelectedMessageHandler::HandleReceivedPlaceJumpSelectedMessage)
			{
				m_messageBus.Subscribe(m_handlerBinding);
			}

			~PlaceJumpSelectedMessageHandler()
			{
				m_messageBus.Unsubscribe(m_handlerBinding);
			}
		};
	}
}
