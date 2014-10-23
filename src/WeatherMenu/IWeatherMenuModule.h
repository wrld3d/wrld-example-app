// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Menu.h"

namespace ExampleApp
{
    namespace WeatherMenu
    {
        class IWeatherMenuModule
        {
        public:
            
            virtual ~IWeatherMenuModule() { }
            
            virtual Menu::IMenuModel& GetWeatherMenuModel() const = 0;
        };
    }
}
