// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"

namespace ExampleApp
{
    namespace WeatherMenu
    {
        namespace SdkModel
        {
            class IWeatherMenuModule
            {
            public:

                virtual ~IWeatherMenuModule() { }

                virtual Menu::View::IMenuModel& GetWeatherMenuModel() const = 0;
            };
        }
    }
}
