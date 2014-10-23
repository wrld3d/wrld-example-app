// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMenuOption.h"
#include "WeatherMenuStateModel.h"
#include "IWeatherController.h"

namespace ExampleApp
{
    namespace WeatherMenu
    {
        class WeatherMenuStateOption : public Menu::IMenuOption
        {
        public:
            WeatherMenuStateOption(WeatherMenuStateModel& weatherStateModel,
                                   IWeatherController& weatherController)
            : m_weatherStateModel(weatherStateModel)
            , m_weatherController(weatherController)
            {
            }
            
            void Select()
            {
                if(m_weatherStateModel.HasTimeState())
                {
                    m_weatherController.SetTime(m_weatherStateModel.GetTimeState());
                }
                if(m_weatherStateModel.HasWeatherState())
                {
                    m_weatherController.SetWeather(m_weatherStateModel.GetWeatherState());
                }
                if(m_weatherStateModel.HasSeasonState())
                {
                    m_weatherController.SetSeason(m_weatherStateModel.GetSeasonState());
                }
                
                m_weatherController.Refresh();
            }
            
        private:
            
            WeatherMenuStateModel m_weatherStateModel;
            IWeatherController& m_weatherController;
        };
    }
}
