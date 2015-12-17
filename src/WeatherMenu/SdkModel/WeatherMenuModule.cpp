// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WeatherMenuModule.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "IFileIO.h"
#include "WeatherMenuDataParser.h"
#include "WeatherMenuStateOption.h"
#include "WeatherController.h"

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
                                                 Metrics::IMetricsService& metricsService)
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

                std::vector<WeatherMenuStateModel> weatherStates;
                if(!WeatherMenuDataParser::ParseWeatherStates(json, weatherStates))
                {
                    Eegeo_ASSERT(false, "Failed to parse weatherstates.json definitions file.");
                }

                m_pWeatherController = Eegeo_NEW(WeatherController)(visualMapService);

                for(std::vector<WeatherMenuStateModel>::iterator it = weatherStates.begin(); it != weatherStates.end(); it++)
                {
                    WeatherMenuStateModel& weatherState = *it;
                    m_pMenuOptionsModel->AddItem(weatherState.GetName(),
                                                 weatherState.GetName(), "", weatherState.GetIcon(),
                                                 Eegeo_NEW(View::WeatherMenuStateOption)(weatherState, messageBus, metricsService));
                }

                m_pWeatherSelectedMessageHandler = Eegeo_NEW(WeatherSelectedMessageHandler)(*m_pWeatherController, messageBus);
            }

            WeatherMenuModule::~WeatherMenuModule()
            {
                Eegeo_DELETE m_pWeatherSelectedMessageHandler;
                Eegeo_DELETE m_pWeatherController;
                Eegeo_DELETE m_pMenuOptionsModel;
                Eegeo_DELETE m_pMenuModel;
            }
        }
    }
}
