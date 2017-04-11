// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IWeatherMenuModule.h"
#include "WeatherMenu.h"
#include "Menu.h"
#include "Helpers.h"
#include "BidirectionalBus.h"
#include "WeatherSelectedMessageHandler.h"
#include "IMetricsService.h"
#include "VisualMap.h"
#include "IAppModeModel.h"
#include "CityThemes.h"
#include "ICallback.h"
#include "ICityThemeChangedObserver.h"

namespace ExampleApp
{
    namespace WeatherMenu
    {
        namespace SdkModel
        {
            class WeatherMenuModule : public IWeatherMenuModule, public Eegeo::Resources::CityThemes::ICityThemeChangedObserver
            {
            public:
                WeatherMenuModule(Eegeo::Helpers::IFileIO& fileio,
                                  VisualMap::SdkModel::IVisualMapService& visualMapService,
                                  ExampleAppMessaging::TMessageBus& messageBus,
                                  Metrics::IMetricsService& metricsService,
                                  const AppModes::SdkModel::IAppModeModel& appModeModel,
                                  Eegeo::Resources::CityThemes::ICityThemesService& cityThemeService,
                                  Eegeo::Resources::CityThemes::ICityThemeRepository& cityThemeRepository);

                ~WeatherMenuModule();

                Menu::View::IMenuModel& GetWeatherMenuModel() const
                {
                    return *m_pMenuModel;
                }
                
                IWeatherController& GetWeatherController() const
                {
                    return *m_pWeatherController;
                }
                
            private:

                void RefreshMenuOptions(const Eegeo::Resources::CityThemes::CityThemeData& themeData);
                virtual void OnThemeRequested(const Eegeo::Resources::CityThemes::CityThemeData& newTheme);
                virtual void OnThemeChanged(const Eegeo::Resources::CityThemes::CityThemeData& newTheme);

                void HandleThemeManifestChanged();

                ExampleAppMessaging::TMessageBus& m_messageBus;
                Metrics::IMetricsService& m_metricsService;
                const AppModes::SdkModel::IAppModeModel& m_appModeModel;
                Eegeo::Resources::CityThemes::ICityThemesService& m_cityThemeService;
                Eegeo::Resources::CityThemes::ICityThemeRepository& m_cityThemeRepository;
                Eegeo::Helpers::TCallback0<WeatherMenuModule> m_themeManifestChangedCallback;

                Menu::View::IMenuModel* m_pMenuModel;
                Menu::View::IMenuOptionsModel* m_pMenuOptionsModel;
                IWeatherController* m_pWeatherController;
                WeatherSelectedMessageHandler* m_pWeatherSelectedMessageHandler;
                std::vector<WeatherMenuStateModel> m_weatherStates;
            };
        }
    }
}
