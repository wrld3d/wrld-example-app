// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "IWeatherController.h"
#include "ICallback.h"
#include "WeatherSelectedMessage.h"

namespace ExampleApp
{
    namespace WeatherMenu
    {
        namespace SdkModel
        {
            class WeatherSelectedMessageHandler : private Eegeo::NonCopyable
            {
                std::shared_ptr<IWeatherController> m_weatherController;
                std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                Eegeo::Helpers::TCallback1<WeatherSelectedMessageHandler, const WeatherSelectedMessage&> m_handlerBinding;

                void OnWeatherSelectedMessage(const WeatherSelectedMessage& message);

            public:
                WeatherSelectedMessageHandler(
                                              const std::shared_ptr<IWeatherController>& weatherController,
                                              const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);

                ~WeatherSelectedMessageHandler();
            };
        }
    }
}
