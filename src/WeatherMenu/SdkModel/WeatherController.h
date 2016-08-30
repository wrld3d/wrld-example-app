// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IWeatherController.h"
#include "VisualMap.h"
#include "IAppModeModel.h"

#include <string>

namespace ExampleApp
{
    namespace WeatherMenu
    {
        namespace SdkModel
        {
            class WeatherController : public IWeatherController
            {
            public:

                WeatherController(const std::shared_ptr<VisualMap::SdkModel::IVisualMapService>& visualMapService);

                void SetWeather(const std::string& weather);
                void SetTime(const std::string& time);
                void SetTheme(const std::string& season);
                void SetState(const std::string& state);

            private:
                std::shared_ptr<VisualMap::SdkModel::IVisualMapService> m_visualMapService;
            };
        }
    }
}
