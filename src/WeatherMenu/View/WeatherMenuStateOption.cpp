// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WeatherMenuStateOption.h"
#include "FlattenButtonViewStateChangedMessage.h"

namespace ExampleApp
{
    namespace WeatherMenu
    {
        namespace View
        {
            WeatherMenuStateOption::WeatherMenuStateOption(
                SdkModel::WeatherMenuStateModel& weatherStateModel,
                ExampleAppMessaging::TMessageBus& messageBus,
                Metrics::IMetricsService& metricsService,
                const AppModes::SdkModel::IAppModeModel& appModeModel)
                : m_weatherStateModel(weatherStateModel)
                , m_messageBus(messageBus)
                , m_metricsService(metricsService)
                , m_appModeModel(appModeModel)
            {
            }

            void WeatherMenuStateOption::Select()
            {
                m_metricsService.SetEvent("UIItem: Weather", "Name", m_weatherStateModel.GetName().c_str());
                
                if (m_appModeModel.GetAppMode() == AppModes::SdkModel::WorldMode)
                {
                    m_messageBus.Publish(FlattenButton::FlattenButtonViewStateChangedMessage(false));
                    m_messageBus.Publish(WeatherSelectedMessage(m_weatherStateModel));
                }

                
            }
        }
    }
}
