// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMapModeModule.h"
#include "MapMode.h"
#include "Rendering.h"
#include "WeatherMenu.h"
#include "Types.h"
#include "IMapModeModel.h"

namespace ExampleApp
{
    namespace MapMode
    {
        namespace SdkModel
        {
            class MapModeModule : public IMapModeModule, private Eegeo::NonCopyable
            {
            public:
                MapModeModule(Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                              WeatherMenu::SdkModel::IWeatherController& weatherController);
                ~MapModeModule();

                IMapModeModel& GetMapModeModel();

            private:
                IMapModeModel* m_pMapModeModel;
                MapModeController* m_pMapModeController;
            };
        }
    }
}