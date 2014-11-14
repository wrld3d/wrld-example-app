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
			ExampleAppMessaging::NativeToUiMessageBus& m_messageBus;
			Eegeo::Helpers::TCallback0<FlattenButtonModelStateChangedObserver> m_flattenStateChangedCallback;

			void HandleFlattenStateChanged()
			{
				m_messageBus.Publish(FlattenButtonModelStateChangedMessage(m_flattenButtonModel.GetFlattened()));
			}

		public:
			FlattenButtonModelStateChangedObserver(IFlattenButtonModel& flattenButtonModel,
			                                       ExampleAppMessaging::NativeToUiMessageBus& messageBus)
				: m_flattenButtonModel(flattenButtonModel)
				, m_messageBus(messageBus)
				, m_flattenStateChangedCallback(this, &FlattenButtonModelStateChangedObserver::HandleFlattenStateChanged)
			{
				m_flattenButtonModel.InsertChangedCallback(m_flattenStateChangedCallback);
			}

			~FlattenButtonModelStateChangedObserver()
			{
				m_flattenButtonModel.RemoveChangedCallback(m_flattenStateChangedCallback);
			}

		};
	}
}
