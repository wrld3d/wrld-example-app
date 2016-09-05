// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMenuOption.h"
#include "WeatherMenuStateModel.h"
#include "BidirectionalBus.h"
#include "WeatherSelectedMessage.h"
#include "IMetricsService.h"

#include <memory>

namespace ExampleApp
{
    namespace WeatherMenu
    {
        namespace View
        {
            class WeatherMenuStateOption : public Menu::View::IMenuOption
            {
            public:
                WeatherMenuStateOption(
                                       SdkModel::WeatherMenuStateModel& weatherStateModel,
                                       const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                       const std::shared_ptr<Metrics::IMetricsService>& metricsService,
                                       const std::shared_ptr<AppModes::SdkModel::IAppModeModel>& appModeModel);

                void Select();

            private:

                SdkModel::WeatherMenuStateModel m_weatherStateModel;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                
                const std::shared_ptr<Metrics::IMetricsService> m_metricsService;
                const std::shared_ptr<const AppModes::SdkModel::IAppModeModel> m_appModeModel;
            };
        }
    }
}
