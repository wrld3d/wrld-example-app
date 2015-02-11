// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WeatherMenuStateOption.h"
#include "FlurryWrapper.h"

namespace ExampleApp
{
    namespace WeatherMenu
    {
        namespace View
        {
            WeatherMenuStateOption::WeatherMenuStateOption(
                SdkModel::WeatherMenuStateModel& weatherStateModel,
                ExampleAppMessaging::TMessageBus& messageBus)
                : m_weatherStateModel(weatherStateModel)
                , m_messageBus(messageBus)
            {
            }

            void WeatherMenuStateOption::Select()
            {
                FLURRY_SET_EVENT("UIItem: Weather", "Name", m_weatherStateModel.GetName().c_str());
                m_messageBus.Publish(WeatherSelectedMessage(m_weatherStateModel));
            }
        }
    }
}
