// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "Types.h"
#include "WeatherMenuStateModel.h"

namespace ExampleApp
{
    namespace WeatherMenu
    {
        namespace SdkModel
        {
            WeatherMenuStateModel::WeatherMenuStateModel(
                std::string name,
                std::string time,
                std::string weather,
                std::string season,
                std::string icon,
                std::string state)
                : m_name(name)
                , m_timeState(time)
                , m_weatherState(weather)
                , m_seasonState(season)
                , m_icon(icon)
            , m_explicitState(state)
            {
            }
        }
    }
}
