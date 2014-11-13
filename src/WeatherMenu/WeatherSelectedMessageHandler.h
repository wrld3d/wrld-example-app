// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "UiToNativeMessageBus.h"
#include "IWeatherController.h"
#include "ICallback.h"
#include "WeatherSelectedMessage.h"

namespace ExampleApp
{
	namespace WeatherMenu
	{
		class WeatherSelectedMessageHandler : private Eegeo::NonCopyable
		{
			IWeatherController& m_weatherController;
			ExampleAppMessaging::UiToNativeMessageBus& m_messageBus;
			Eegeo::Helpers::TCallback1<WeatherSelectedMessageHandler, const WeatherSelectedMessage&> m_handlerBinding;

			void HandleReceivedWeatherSelectedMessage(const WeatherSelectedMessage& message);

		public:
			WeatherSelectedMessageHandler(
			    IWeatherController& weatherController,
			    ExampleAppMessaging::UiToNativeMessageBus& messageBus);

			~WeatherSelectedMessageHandler();
		};
	}
}
