// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IWorldPinInFocusViewModel.h"
#include "ICallback.h"
#include "NativeToUiMessageBus.h"
#include "WorldPinGainedFocusMessage.h"
#include "WorldPinLostFocusMessage.h"
#include "WorldPinInFocusChangedLocationMessage.h"

namespace ExampleApp
{
	namespace WorldPins
	{
		class WorldPinInFocusObserver : private Eegeo::NonCopyable
		{
            IWorldPinInFocusViewModel& m_worldPinInFocusViewModel;
			ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;
			Eegeo::Helpers::TCallback1<WorldPinInFocusObserver, const WorldPinGainedFocusMessage&> m_gainedFocusHandler;
			Eegeo::Helpers::TCallback1<WorldPinInFocusObserver, const WorldPinLostFocusMessage&> m_lostFocusHandler;
			Eegeo::Helpers::TCallback1<WorldPinInFocusObserver, const WorldPinInFocusChangedLocationMessage&> m_focusScreenLocationUpdatedHandler;

            void HandleReceivedWorldPinGainedFocusMessage(const WorldPinGainedFocusMessage& message)
			{
				m_worldPinInFocusViewModel.Open(message.FocussedModel(), message.ScreenLocation());
      
			}

			void HandleReceivedWorldPinLostFocusMessage(const WorldPinLostFocusMessage& message)
			{
				m_worldPinInFocusViewModel.Close();
			}

			void HandleReceivedWorldPinInFocusChangedLocationMessage(const WorldPinInFocusChangedLocationMessage& message)
			{
				m_worldPinInFocusViewModel.UpdateScreenLocation(message.ScreenLocation());
			}

		public:
			WorldPinInFocusObserver(
                                         IWorldPinInFocusViewModel& worldPinInFocusViewModel,
                                         ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
				: m_worldPinInFocusViewModel(worldPinInFocusViewModel)
				, m_nativeToUiMessageBus(nativeToUiMessageBus)
				, m_gainedFocusHandler(this, &WorldPinInFocusObserver::HandleReceivedWorldPinGainedFocusMessage)
				, m_lostFocusHandler(this, &WorldPinInFocusObserver::HandleReceivedWorldPinLostFocusMessage)
				, m_focusScreenLocationUpdatedHandler(this, &WorldPinInFocusObserver::HandleReceivedWorldPinInFocusChangedLocationMessage)
			{
				m_nativeToUiMessageBus.Subscribe(m_gainedFocusHandler);
				m_nativeToUiMessageBus.Subscribe(m_lostFocusHandler);
				m_nativeToUiMessageBus.Subscribe(m_focusScreenLocationUpdatedHandler);
			}

			~WorldPinInFocusObserver()
			{
				m_nativeToUiMessageBus.Unsubscribe(m_gainedFocusHandler);
				m_nativeToUiMessageBus.Unsubscribe(m_lostFocusHandler);
				m_nativeToUiMessageBus.Unsubscribe(m_focusScreenLocationUpdatedHandler);
			}
		};
	}
}
