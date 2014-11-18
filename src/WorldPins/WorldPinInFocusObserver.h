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

            void HandleReceivedWorldPinGainedFocusMessage(const WorldPinGainedFocusMessage& message);
            void HandleReceivedWorldPinLostFocusMessage(const WorldPinLostFocusMessage& message);
            void HandleReceivedWorldPinInFocusChangedLocationMessage(const WorldPinInFocusChangedLocationMessage& message);

		public:
			WorldPinInFocusObserver(IWorldPinInFocusViewModel& worldPinInFocusViewModel,
                                    ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);

            ~WorldPinInFocusObserver();
		};
	}
}
