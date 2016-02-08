// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IWeatherMenuStateModel.h"
#include "Types.h"
#include <string>

namespace ExampleApp
{
    namespace WeatherMenu
    {
        namespace SdkModel
        {
            class WeatherMenuStateModel : public IWeatherMenuStateModel
            {
            public:

                WeatherMenuStateModel(std::string name, std::string time, std::string weather, std::string season, std::string icon, std::string explicitState);

                const bool HasTimeState() const
                {
                    return !m_timeState.empty();
                }
                const bool HasWeatherState() const
                {
                    return !m_weatherState.empty();
                }
                const bool HasSeasonState() const
                {
                    return !m_seasonState.empty();
                }
                const bool HasExplicitState() const
                {
                    return !m_explicitState.empty();
                }

                const std::string& GetName() const
                {
                    return m_name;
                }
                const std::string& GetTimeState() const
                {
                    return m_timeState;
                }
                const std::string& GetWeatherState() const
                {
                    return m_weatherState;
                }
                const std::string& GetSeasonState() const
                {
                    return m_seasonState;
                }
                const std::string& GetIcon() const
                {
                    return m_icon;
                }
                const std::string& GetExplicitState() const
                {
                    return m_explicitState;
                }

            private:

                std::string m_name;
                std::string m_timeState;
                std::string m_weatherState;
                std::string m_seasonState;
                std::string m_explicitState;
                std::string m_icon;
            };
        }
    }
}
