// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMenuOption.h"
#include "WeatherMenuStateModel.h"
#include "BidirectionalBus.h"
#include "WeatherSelectedMessage.h"

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
                    ExampleAppMessaging::TMessageBus& messageBus);

                void Select();

            private:

                SdkModel::WeatherMenuStateModel m_weatherStateModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
            };
        }
    }
}
