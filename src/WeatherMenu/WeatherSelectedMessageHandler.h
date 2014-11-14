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

			void HandleReceivedWeatherSelectedMessage(const WeatherSelectedMessage& message)
			{
				const WeatherMenuStateModel& model = message.Model();

				if(model.HasTimeState())
				{
					m_weatherController.SetTime(model.GetTimeState());
				}
				if(model.HasWeatherState())
				{
					m_weatherController.SetWeather(model.GetWeatherState());
				}
				if(model.HasSeasonState())
				{
					m_weatherController.SetSeason(model.GetSeasonState());
				}

				m_weatherController.Refresh();
			}

		public:
			WeatherSelectedMessageHandler(
			    IWeatherController& weatherController,
			    ExampleAppMessaging::UiToNativeMessageBus& messageBus)
				: m_weatherController(weatherController)
				, m_messageBus(messageBus)
				, m_handlerBinding(this, &WeatherSelectedMessageHandler::HandleReceivedWeatherSelectedMessage)
			{
				m_messageBus.Subscribe(m_handlerBinding);
			}

			~WeatherSelectedMessageHandler()
			{
				m_messageBus.Unsubscribe(m_handlerBinding);
			}
		};
	}
}
