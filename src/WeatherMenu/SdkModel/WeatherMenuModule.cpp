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
            class WeatherMenuModel : public Menu::View::MenuModel
            {
            };
            
            class WeatherOptionsModel : public Menu::View::MenuOptionsModel
            {
            public:
                WeatherOptionsModel(const std::shared_ptr<WeatherMenuModel>& menuModel)
                : m_menuModel(menuModel)
                , MenuOptionsModel(*menuModel)
                {
                }
            private:
                std::shared_ptr<WeatherMenuModel> m_menuModel;
            };
            
            void WeatherMenuModule::Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            {
                builder->registerType<WeatherController>().as<IWeatherController>().singleInstance();
                builder->registerType<WeatherSelectedMessageHandler>().singleInstance();
                builder->registerType<WeatherMenuModel>().singleInstance();
                builder->registerType<WeatherOptionsModel>().singleInstance();
/*              m_builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       auto optionsModel = std::make_shared<Menu::View::MenuOptionsModel>(context.resolve<Menu::View::MenuModel>());
                                                       auto fileIO = context.resolve<Eegeo::Helpers::IFileIO>();
                                                       auto metricsService = context.resolve<Metrics::IMetricsService>();
                                                       auto appModeModel = context.resolve<AppModes::SdkModel::IAppModeModel>();
                                                       
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
                                                                                 Eegeo_NEW(View::WeatherMenuStateOption)(weatherState, *context.resolve<ExampleAppMessaging::TMessageBus>(), *metricsService, *appModeModel));
                                                       }
                                                       return optionsModel;
                                                   }).singleInstance();*/
            }
        }
    }
}
