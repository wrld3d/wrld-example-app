// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WeatherMenuModule.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "IFileIO.h"
#include "WeatherMenuDataParser.h"
#include "WeatherMenuStateOption.h"
#include "WeatherController.h"
#include "ICityThemesService.h"
#include "ICityThemeRepository.h"
#include "CityThemeData.h"

#include <vector>
#include <string>
#include <fstream>

namespace ExampleApp
{
    namespace WeatherMenu
    {
        namespace SdkModel
        {
            WeatherMenuModule::WeatherMenuModule(Eegeo::Helpers::IFileIO& fileIO,
                                                 VisualMap::SdkModel::IVisualMapService& visualMapService,
                                                 ExampleAppMessaging::TMessageBus& messageBus,
                                                 Metrics::IMetricsService& metricsService,
                                                 const AppModes::SdkModel::IAppModeModel& appModeModel,
                                                 Eegeo::Resources::CityThemes::ICityThemesService& cityThemeService,
                                                 Eegeo::Resources::CityThemes::ICityThemeRepository& cityThemeRepository)
            : m_messageBus(messageBus)
            , m_metricsService(metricsService)
            , m_appModeModel(appModeModel)
            , m_cityThemeService(cityThemeService)
            , m_cityThemeRepository(cityThemeRepository)
            , m_themeManifestChangedCallback(this, &WeatherMenuModule::HandleThemeManifestChanged)
            , m_weatherStates()
            {
                m_pMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                m_pMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pMenuModel);

                std::fstream stream;
                size_t size;

                if(!fileIO.OpenFile(stream, size, "weatherstates.json"))
                {
                    Eegeo_ASSERT(false, "Failed to load weatherstates.json definitions file.");
                }

                std::string json((std::istreambuf_iterator<char>(stream)),
                                 (std::istreambuf_iterator<char>()));

                if(!WeatherMenuDataParser::ParseWeatherStates(json, m_weatherStates))
                {
                    Eegeo_ASSERT(false, "Failed to parse weatherstates.json definitions file.");
                }

                m_pWeatherController = Eegeo_NEW(WeatherController)(visualMapService);

                m_pWeatherSelectedMessageHandler = Eegeo_NEW(WeatherSelectedMessageHandler)(*m_pWeatherController, messageBus);

                RefreshMenuOptions(m_cityThemeService.GetCurrentTheme());

                m_cityThemeService.SubscribeSharedThemeDataChanged(m_themeManifestChangedCallback);
                m_cityThemeService.RegisterThemeChangedObserver(*this);
            }

            WeatherMenuModule::~WeatherMenuModule()
            {
                m_cityThemeService.UnregisterThemeChangedObserver(*this);
                m_cityThemeService.UnsubscribeSharedThemeDataChanged(m_themeManifestChangedCallback);
                Eegeo_DELETE m_pWeatherSelectedMessageHandler;
                Eegeo_DELETE m_pWeatherController;
                Eegeo_DELETE m_pMenuOptionsModel;
                Eegeo_DELETE m_pMenuModel;
            }

            void WeatherMenuModule::RefreshMenuOptions(const Eegeo::Resources::CityThemes::CityThemeData& themeData)
            {
                for(std::vector<WeatherMenuStateModel>::iterator it = m_weatherStates.begin(); it != m_weatherStates.end(); ++it)
                {
                    WeatherMenuStateModel& weatherState = *it;
                    m_pMenuOptionsModel->RemoveItem(weatherState.GetName());
                }

                for(std::vector<WeatherMenuStateModel>::iterator it = m_weatherStates.begin(); it != m_weatherStates.end(); ++it)
                {
                    WeatherMenuStateModel& weatherState = *it;
                    std::string time = weatherState.HasTimeState() ? weatherState.GetTimeState() : "Day";
                    std::string weather = weatherState.HasWeatherState() ? weatherState.GetWeatherState() : "Default";

                    bool shouldAdd = !weatherState.HasSeasonState() || m_cityThemeRepository.HasThemeWithNameContaining(weatherState.GetSeasonState());
                    shouldAdd &= themeData.IsCityThemeStateSupported(time + weather);

                    if (shouldAdd)
                    {
                        m_pMenuOptionsModel->AddItem(
                            weatherState.GetName(),
                            weatherState.GetName(), "", weatherState.GetIcon(),
                            Eegeo_NEW(View::WeatherMenuStateOption)(weatherState, m_messageBus, m_metricsService, m_appModeModel));
                    }
                }
            }

            void WeatherMenuModule::HandleThemeManifestChanged()
            {
                RefreshMenuOptions(m_cityThemeService.GetCurrentTheme());
            }

            void WeatherMenuModule::OnThemeRequested(const Eegeo::Resources::CityThemes::CityThemeData& newTheme)
            {

            }

            void WeatherMenuModule::OnThemeChanged(const Eegeo::Resources::CityThemes::CityThemeData& newTheme)
            {
                RefreshMenuOptions(newTheme);
            }

        }
    }
}
