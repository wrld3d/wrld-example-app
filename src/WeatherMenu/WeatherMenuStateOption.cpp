// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WeatherMenuStateOption.h"

namespace ExampleApp
{
	namespace WeatherMenu
	{
		WeatherMenuStateOption::WeatherMenuStateOption(
			WeatherMenuStateModel& weatherStateModel,
			ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
			: m_weatherStateModel(weatherStateModel)
			, m_uiToNativeMessageBus(uiToNativeMessageBus)
		{
		}

		void WeatherMenuStateOption::Select()
		{
			m_uiToNativeMessageBus.Publish(WeatherSelectedMessage(m_weatherStateModel));
		}
	}
}
