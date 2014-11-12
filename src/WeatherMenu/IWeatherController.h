// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
	namespace WeatherMenu
	{
		class IWeatherController
		{
		public:
			virtual ~IWeatherController() {};

			virtual void SetWeather(const std::string& weather) = 0;
			virtual void SetTime(const std::string& time) = 0;
			virtual void SetSeason(const std::string& season) = 0;
			virtual void Refresh() = 0;
		};
	}
}
