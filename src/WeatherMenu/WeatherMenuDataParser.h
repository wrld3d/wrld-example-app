// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "WeatherMenu.h"
#include "WeatherMenuStateModel.h"
#include <string>
#include <vector>


namespace ExampleApp
{
    namespace WeatherMenu
    {
        namespace WeatherMenuDataParser
        {
            bool ParseWeatherStates(const std::string& json, std::vector<SdkModel::WeatherMenuStateModel>&  out_weatherStates);
        }
    }
}
