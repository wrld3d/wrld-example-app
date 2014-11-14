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
			ExampleAppMessaging::UiToNativeMessageBus& m_messageBus;
			Eegeo::Helpers::TCallback1<FlattenButtonViewStateChangedObserver, const FlattenButtonViewStateChangedMessage&> m_handlerBinding;

			void HandleReceivedFlattenButtonStateChangedMessage(const FlattenButtonViewStateChangedMessage& message)
			{
				if(message.IsFlattened())
				{
					m_flattenButtonModel.Flatten();
				}
				else
				{
					m_flattenButtonModel.Unflatten();
				}
			}

		public:
			FlattenButtonViewStateChangedObserver(IFlattenButtonModel& flattenButtonModel,
			                                      ExampleAppMessaging::UiToNativeMessageBus& messageBus)
				: m_flattenButtonModel(flattenButtonModel)
				, m_messageBus(messageBus)
				, m_handlerBinding(this, &FlattenButtonViewStateChangedObserver::HandleReceivedFlattenButtonStateChangedMessage)
			{
				m_messageBus.Subscribe(m_handlerBinding);
			}

			~FlattenButtonViewStateChangedObserver()
			{
				m_messageBus.Unsubscribe(m_handlerBinding);
			}

		};
	}
}
