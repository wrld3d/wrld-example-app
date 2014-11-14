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
			ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
			Eegeo::Helpers::TCallback1<PlaceJumpSelectedMessageHandler, const PlaceJumpSelectedMessage&> m_handlerBinding;

			void HandleReceivedPlaceJumpSelectedMessage(const PlaceJumpSelectedMessage& message);

		public:
			PlaceJumpSelectedMessageHandler(
			    IPlaceJumpController& placeJumpController,
			    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);

			~PlaceJumpSelectedMessageHandler();
		};
	}
}
