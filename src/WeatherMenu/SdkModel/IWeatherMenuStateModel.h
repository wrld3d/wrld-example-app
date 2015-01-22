// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"
#include <string>

namespace ExampleApp
{
    namespace WeatherMenu
    {
        namespace SdkModel
        {
            class IWeatherMenuStateModel
            {
            public:
                virtual ~IWeatherMenuStateModel() { }

                virtual const bool HasTimeState() const = 0;
                virtual const bool HasWeatherState() const = 0;
                virtual const bool HasSeasonState() const = 0;

                virtual const std::string& GetName() const = 0;
                virtual const std::string& GetTimeState() const = 0;
                virtual const std::string& GetWeatherState() const = 0;
                virtual const std::string& GetSeasonState() const = 0;
                virtual const std::string& GetIcon() const = 0;
            };
        }
    }
}
