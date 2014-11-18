// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "UiToNativeMessageBus.h"
#include "ICallback.h"
#include "IFlattenButtonModel.h"

namespace ExampleApp
{
	namespace FlattenButton
	{
		class FlattenButtonViewStateChangedObserver
		{
			IFlattenButtonModel& m_flattenButtonModel;
			ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
			Eegeo::Helpers::TCallback1<FlattenButtonViewStateChangedObserver, const FlattenButtonViewStateChangedMessage&> m_handlerBinding;

			void HandleReceivedFlattenButtonStateChangedMessage(const FlattenButtonViewStateChangedMessage& message);

		public:
			FlattenButtonViewStateChangedObserver(IFlattenButtonModel& flattenButtonModel,
			                                      ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);

			~FlattenButtonViewStateChangedObserver();
		};
	}
}
