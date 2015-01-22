// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WeatherMenuStateModel.h"

namespace ExampleApp
{
    namespace WeatherMenu
    {
        class WeatherSelectedMessage
        {
            SdkModel::WeatherMenuStateModel m_weatherStateModel;

        public:
            WeatherSelectedMessage(const SdkModel::WeatherMenuStateModel& weatherStateModel);

            const SdkModel::WeatherMenuStateModel& Model() const;
        };
    }
}
