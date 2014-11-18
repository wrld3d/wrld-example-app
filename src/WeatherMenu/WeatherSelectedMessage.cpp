// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WeatherSelectedMessage.h"

namespace ExampleApp
{
	namespace WeatherMenu
	{
		WeatherSelectedMessage::WeatherSelectedMessage(const WeatherMenuStateModel& weatherStateModel)
			: m_weatherStateModel(weatherStateModel)
		{
		}

		const WeatherMenuStateModel& WeatherSelectedMessage::Model() const
		{
			return m_weatherStateModel;
		}
	}
}
