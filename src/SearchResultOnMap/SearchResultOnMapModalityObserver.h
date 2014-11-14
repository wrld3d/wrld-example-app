// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "UiToNativeMessageBus.h"
#include "ICallback.h"
#include "ModalityChangedMessage.h"
#include "IWorldPinsScaleController.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		class SearchResultOnMapModalityObserver : private Eegeo::NonCopyable
		{
			WorldPins::IWorldPinsScaleController& m_worldPinsScaleController;
			ExampleAppMessaging::UiToNativeMessageBus& m_messageBus;
			Eegeo::Helpers::TCallback1<SearchResultOnMapModalityObserver, const Modality::ModalityChangedMessage&> m_handlerBinding;

			void HandleReceivedModalityChangedMessage(const Modality::ModalityChangedMessage& message)
			{
				m_worldPinsScaleController.SetModality(message.Modality());
			}

		public:
			SearchResultOnMapModalityObserver(WorldPins::IWorldPinsScaleController& worldPinsScaleController,
			                                  ExampleAppMessaging::UiToNativeMessageBus& messageBus)
				: m_worldPinsScaleController(worldPinsScaleController)
				, m_messageBus(messageBus)
				, m_handlerBinding(this, &SearchResultOnMapModalityObserver::HandleReceivedModalityChangedMessage)
			{
				m_messageBus.Subscribe(m_handlerBinding);
			}

			~SearchResultOnMapModalityObserver()
			{
				m_messageBus.Unsubscribe(m_handlerBinding);
			}
		};
	}
}
