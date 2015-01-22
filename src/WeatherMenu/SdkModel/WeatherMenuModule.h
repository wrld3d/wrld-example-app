// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IWeatherMenuModule.h"
#include "WeatherMenu.h"
#include "Menu.h"
#include "Helpers.h"
#include "CityThemes.h"
#include "BidirectionalBus.h"
#include "WeatherSelectedMessageHandler.h"

namespace ExampleApp
{
    namespace WeatherMenu
    {
        namespace SdkModel
        {
            class WeatherMenuModule : public IWeatherMenuModule
            {
            public:
                WeatherMenuModule(Eegeo::Helpers::IFileIO& fileio,
                                  Eegeo::Resources::CityThemes::ICityThemesService& themesService,
                                  Eegeo::Resources::CityThemes::ICityThemesUpdater& themesUpdater,
                                  ExampleAppMessaging::TMessageBus& messageBus);

                ~WeatherMenuModule();

                Menu::View::IMenuModel& GetWeatherMenuModel() const
                {
                    return *m_pMenuModel;
                }
            private:

                Menu::View::IMenuModel* m_pMenuModel;
                Menu::View::IMenuOptionsModel* m_pMenuOptionsModel;
                IWeatherController* m_pWeatherController;
                WeatherSelectedMessageHandler* m_pWeatherSelectedMessageHandler;
            };
        }
    }
}
