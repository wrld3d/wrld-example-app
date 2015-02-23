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
                , m_currentTheme("Summer")
                , m_currentState("DayDefault")
                , m_themesService(themesService)
                , m_themesUpdater(themesUpdater)
            {
            }

            void WeatherController::SetTime(const std::string &time)
            {
                if(m_currentTheme.compare(time) != 0)
                {
                    m_currentTime = time;
                    SetState(m_currentTime + m_currentWeather);
                }
            }

            void WeatherController::SetWeather(const std::string &weather)
            {
                if(m_currentWeather.compare(weather) != 0)
                {
                    m_currentWeather = weather;
                    SetState(m_currentTime + m_currentWeather);
                }
            }

            void WeatherController::SetTheme(const std::string &theme)
            {
                if(m_currentTheme.compare(theme) != 0)
                {
                    m_currentTheme = theme;
                    RefreshTheme();
                }
            }
            
            void WeatherController::SetState(const std::string &state)
            {
                if(m_currentState.compare(state) != 0)
                {
                    m_currentState = state;
                    RefreshTheme();
                }
            }

            void WeatherController::RefreshTheme()
            {
                EXAMPLE_LOG("Changing season to: %s\n", m_currentTheme.c_str());
                m_themesUpdater.SetThemeMustContain(m_currentTheme);

                EXAMPLE_LOG("Changing state to: %s\n", m_currentState.c_str());
                m_themesService.RequestTransitionToState(m_currentState, 1);
            }
        }
    }
}
