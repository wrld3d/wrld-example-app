// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "WeatherMenuStateModel.h"

namespace ExampleApp
{
	namespace WeatherMenu
	{
		class WeatherSelectedMessage
		{
            WeatherMenuStateModel m_weatherStateModel;

		public:
			WeatherSelectedMessage(const WeatherMenuStateModel& weatherStateModel)
			: m_weatherStateModel(weatherStateModel)
			{
			}

			const WeatherMenuStateModel& Model() const
			{
				return m_weatherStateModel;
			}
		};
	}
}
