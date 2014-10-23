// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IWeatherController.h"
#include "CityThemes.h"
#include <string>

namespace ExampleApp
{
    namespace WeatherMenu
    {
        class WeatherController : public IWeatherController
        {
        public:
            
            WeatherController(Eegeo::Resources::CityThemes::ICityThemesService& themesService,
                              Eegeo::Resources::CityThemes::ICityThemesUpdater& themesUpdater);
            
            void SetWeather(const std::string& weather);
            void SetTime(const std::string& time);
            void SetSeason(const std::string& season);
            void Refresh();
            
        private:
            
            std::string m_currentWeather;
            std::string m_currentTime;
            std::string m_currentSeason;
            
            Eegeo::Resources::CityThemes::ICityThemesService& m_themesService;
            Eegeo::Resources::CityThemes::ICityThemesUpdater& m_themesUpdater;
        };
    }
}
