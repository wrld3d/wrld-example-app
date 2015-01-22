// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "UiToNativeMessageBus.h"
#include "ICallback.h"
#include "ModalityChangedMessage.h"
#include "IWorldPinsScaleController.h"

namespace ExampleApp
{
	namespace WorldPins
	{
		class WorldPinsModalityObserver : private Eegeo::NonCopyable
		{
			WorldPins::IWorldPinsScaleController& m_worldPinsScaleController;
			ExampleAppMessaging::UiToNativeMessageBus& m_messageBus;
			Eegeo::Helpers::TCallback1<WorldPinsModalityObserver, const Modality::ModalityChangedMessage&> m_handlerBinding;

            void HandleReceivedModalityChangedMessage(const Modality::ModalityChangedMessage& message);

		public:
			WorldPinsModalityObserver(WorldPins::IWorldPinsScaleController& worldPinsScaleController,
                                      ExampleAppMessaging::UiToNativeMessageBus& messageBus);

            ~WorldPinsModalityObserver();
		};
	}
}
