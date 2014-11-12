// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

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
bool ParseWeatherStates(const std::string& json, std::vector<WeatherMenuStateModel>&  out_weatherStates);
}
}
}
