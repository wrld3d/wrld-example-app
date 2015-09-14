// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MapMode.h"
#include "Rendering.h"
#include "WeatherMenu.h"

#include <string>
#include <ICallback.h>

namespace ExampleApp
{
    namespace MapMode
    {
        namespace SdkModel
        {
            class MapModeController
            {
            public:
                MapModeController(IMapModeModel& mapModeModel,
                                  Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                  WeatherMenu::SdkModel::IWeatherController& weatherController);

                ~MapModeController();

            private:
                IMapModeModel& m_mapModeModel;
                std::string m_previousThemeState;

                Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
                WeatherMenu::SdkModel::IWeatherController& m_weatherController;

                void OnMapModeChanged();
                Eegeo::Helpers::TCallback0<MapModeController> m_onMapModeChangedCallback;
            };
        }
    }
}