// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WeatherMenuModule.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "IFileIO.h"
#include "WeatherMenuDataParser.h"
#include "WeatherMenuStateOption.h"
#include "WeatherController.h"
#include "WeatherSelectedMessageHandler.h"
#include "IVisualMapService.h"
#include <vector>
#include <string>
#include <fstream>

namespace ExampleApp
{
    namespace WeatherMenu
    {
        namespace SdkModel
        {
            namespace
            {
            }
            
            void WeatherMenuModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<WeatherController>().as<IWeatherController>().singleInstance();
                builder->registerType<WeatherSelectedMessageHandler>().singleInstance();
                builder->registerType<View::WeatherMenuModel>().singleInstance();
                builder->registerType<View::WeatherOptionsModel>().singleInstance();
            }
            
            void WeatherMenuModule::RegisterUiLeaves()
            {
            	RegisterLeaf<View::WeatherMenuModel>();
            	RegisterLeaf<View::WeatherOptionsModel>();
            }

            void WeatherMenuModule::RegisterNativeLeaves()
            {
                RegisterLeaf<WeatherSelectedMessageHandler>();

                auto optionsModel = Resolve<View::WeatherOptionsModel>();
                auto fileIO = Resolve<Eegeo::Helpers::IFileIO>();
                
                std::fstream stream;
                size_t size;
                
                if(!fileIO->OpenFile(stream, size, "weatherstates.json"))
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
                
                for(std::vector<WeatherMenuStateModel>::iterator it = weatherStates.begin(); it != weatherStates.end(); it++)
                {
                    WeatherMenuStateModel& weatherState = *it;
                    optionsModel->AddItem(weatherState.GetName(),
                                          weatherState.GetName(), "", weatherState.GetIcon(),
                                          Eegeo_NEW(View::WeatherMenuStateOption)(weatherState, Resolve<ExampleAppMessaging::TMessageBus>(), Resolve<Metrics::IMetricsService>(), Resolve<AppModes::SdkModel::IAppModeModel>()));
                }
            }
        }
    }
}
