// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WeatherSelectedMessageHandler.h"

namespace ExampleApp
{
    namespace WeatherMenu
    {
        namespace SdkModel
        {
            void WeatherSelectedMessageHandler::OnWeatherSelectedMessage(const WeatherSelectedMessage& message)
            {
                const WeatherMenuStateModel& model = message.Model();

                if(model.HasTimeState())
                {
                    m_weatherController.SetTime(model.GetTimeState());
                }
                if(model.HasWeatherState())
                {
                    m_weatherController.SetWeather(model.GetWeatherState());
                }
                if(model.HasSeasonState())
                {
                    m_weatherController.SetTheme(model.GetSeasonState());
                }

                if(model.HasExplicitState())
                {
                    m_weatherController.SetState(model.GetExplicitState());
                }
            }

            WeatherSelectedMessageHandler::WeatherSelectedMessageHandler(
                IWeatherController& weatherController,
                ExampleAppMessaging::TMessageBus& messageBus)
                : m_weatherController(weatherController)
                , m_messageBus(messageBus)
                , m_handlerBinding(this, &WeatherSelectedMessageHandler::OnWeatherSelectedMessage)
            {
                m_messageBus.SubscribeNative(m_handlerBinding);
            }

            WeatherSelectedMessageHandler::~WeatherSelectedMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_handlerBinding);
            }
        }
    }
}
