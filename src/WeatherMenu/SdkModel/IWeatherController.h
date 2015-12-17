// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace WeatherMenu
    {
        namespace SdkModel
        {
            class IWeatherController
            {
            public:
                virtual ~IWeatherController() {};

                virtual void SetWeather(const std::string& weather) = 0;
                virtual void SetTime(const std::string& time) = 0;
                virtual void SetTheme(const std::string& season) = 0;
                virtual void SetState(const std::string& state) = 0;
            };
        }
    }
}
