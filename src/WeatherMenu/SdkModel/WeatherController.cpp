// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WeatherController.h"
#include "ICityThemesService.h"
#include "ICityThemesUpdater.h"
#include "Logger.h"

namespace ExampleApp
{
    namespace WeatherMenu
    {
        namespace SdkModel
        {
            WeatherController::WeatherController(Eegeo::Resources::CityThemes::ICityThemesService& themesService,
                                                 Eegeo::Resources::CityThemes::ICityThemesUpdater& themesUpdater)
                : m_currentWeather("Default")
                , m_currentTime("Day")
                , m_currentSeason("Summer")
                , m_themesService(themesService)
                , m_themesUpdater(themesUpdater)
            {
            }

            void WeatherController::SetTime(const std::string &time)
            {
                m_currentTime = time;
            }

            void WeatherController::SetWeather(const std::string &weather)
            {
                m_currentWeather = weather;
            }

            void WeatherController::SetSeason(const std::string &season)
            {
                m_currentSeason = season;
            }

            void WeatherController::Refresh()
            {
                EXAMPLE_LOG("Changing season to: %s\n", m_currentSeason.c_str());
                m_themesUpdater.SetThemeMustContain(m_currentSeason);

                std::string themeStateName = m_currentTime + m_currentWeather;
                EXAMPLE_LOG("Changing state to: %s\n", themeStateName.c_str());
                m_themesService.RequestTransitionToState(themeStateName, 1);
            }
        }
    }
}
