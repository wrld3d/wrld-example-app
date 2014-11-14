// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "FlattenButtonViewStateChangedObserver.h"

namespace ExampleApp
{
	namespace FlattenButton
	{
		FlattenButtonViewStateChangedObserver::FlattenButtonViewStateChangedObserver(IFlattenButtonModel& flattenButtonModel,
											  ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
			: m_flattenButtonModel(flattenButtonModel)
			, m_uiToNativeMessageBus(uiToNativeMessageBus)
			, m_handlerBinding(this, &FlattenButtonViewStateChangedObserver::HandleReceivedFlattenButtonStateChangedMessage)
		{
			m_uiToNativeMessageBus.Subscribe(m_handlerBinding);
		}

		FlattenButtonViewStateChangedObserver::~FlattenButtonViewStateChangedObserver()
		{
			m_uiToNativeMessageBus.Unsubscribe(m_handlerBinding);
		}

		void FlattenButtonViewStateChangedObserver::HandleReceivedFlattenButtonStateChangedMessage(const FlattenButtonViewStateChangedMessage& message)
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
	}
}
