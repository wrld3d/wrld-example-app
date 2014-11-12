// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "Types.h"
#include "WeatherMenuStateModel.h"

namespace ExampleApp
{
namespace WeatherMenu
{
WeatherMenuStateModel::WeatherMenuStateModel(
    std::string name,
    std::string time,
    std::string weather,
    std::string season,
    std::string icon)
	: m_name(name)
	, m_timeState(time)
	, m_weatherState(weather)
	, m_seasonState(season)
	, m_icon(icon)
{
}
}
}
