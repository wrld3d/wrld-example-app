// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WeatherSelectedMessage.h"

namespace ExampleApp
{
    namespace WeatherMenu
    {
        WeatherSelectedMessage::WeatherSelectedMessage(const SdkModel::WeatherMenuStateModel& weatherStateModel)
            : m_weatherStateModel(weatherStateModel)
        {
        }

        const SdkModel::WeatherMenuStateModel& WeatherSelectedMessage::Model() const
        {
            return m_weatherStateModel;
        }
    }
}
