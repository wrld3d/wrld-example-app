// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IModalityModel.h"
#include "ISearchQueryPerformer.h"
#include "ICallback.h"
#include "UiToNativeMessageBus.h"
#include "ModalityChangedMessage.h"

namespace ExampleApp
{
	namespace Modality
	{
		class ModalityObserver : private Eegeo::NonCopyable
		{
			IModalityModel& m_modalityModel;
			ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
			Eegeo::Helpers::TCallback0<ModalityObserver> m_modalityChangedCallback;

			void HandleModalityChanged();

		public:
			ModalityObserver(IModalityModel& modalityModel,
			                 ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);

			~ModalityObserver();
		};
	}
}
