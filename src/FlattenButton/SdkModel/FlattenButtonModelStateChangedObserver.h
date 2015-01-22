// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "NativeToUiMessageBus.h"
#include "ICallback.h"
#include "IFlattenButtonModel.h"
#include "FlattenButtonViewStateChangedObserver.h"
#include "FlattenButtonModelStateChangedMessage.h"

namespace ExampleApp
{
	namespace FlattenButton
	{
		class FlattenButtonModelStateChangedObserver
		{
			IFlattenButtonModel& m_flattenButtonModel;
			ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;
			Eegeo::Helpers::TCallback0<FlattenButtonModelStateChangedObserver> m_flattenStateChangedCallback;

			void HandleFlattenStateChanged();

		public:
			FlattenButtonModelStateChangedObserver(IFlattenButtonModel& flattenButtonModel,
			                                       ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);

			~FlattenButtonModelStateChangedObserver();
		};
	}
}
