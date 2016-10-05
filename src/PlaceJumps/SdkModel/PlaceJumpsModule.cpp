// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <vector>
#include <string>
#include <fstream>
#include "PlaceJumpsModule.h"
#include "PlaceJumpsDataParser.h"
#include "PlaceJumpsModel.h"
#include "MenuModel.h"
#include "IFileIO.h"
#include "SettingsMenu.h"
#include "MenuOptionsModel.h"
#include "PlaceJumpMenuOption.h"
#include "PlaceJumpController.h"
#include "PlaceJumpSelectedMessageHandler.h"
#include "ICameraTransitionController.h"

namespace ExampleApp
{
    namespace PlaceJumps
    {
        namespace SdkModel
        {            
            void PlaceJumpsModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<PlaceJumpController>().as<IPlaceJumpController>().singleInstance();
                builder->registerType<View::PlaceJumpMenuModel>().singleInstance();
                builder->registerType<View::PlaceJumpMenuOptionsModel>().singleInstance();
                builder->registerType<PlaceJumpSelectedMessageHandler>().singleInstance();
            }
            
            void PlaceJumpsModule::RegisterNativeLeaves()
            {
                RegisterLeaf<PlaceJumpSelectedMessageHandler>();
                
                auto fileIO = Resolve<Eegeo::Helpers::IFileIO>();
                auto optionsModel = Resolve<View::PlaceJumpMenuOptionsModel>();
                std::fstream stream;
                size_t size;
                
                if(!fileIO->OpenFile(stream, size, "placejumps.json"))
                {
                    Eegeo_ASSERT(false, "Failed to load placejumps.json definitions file.");
                }
                
                std::string json((std::istreambuf_iterator<char>(stream)),
                                 (std::istreambuf_iterator<char>()));
                
                std::vector<View::PlaceJumpModel> placeJumps;
                if(!View::PlaceJumpsDataParser::ParsePlaceJumps(json, placeJumps))
                {
                    Eegeo_ASSERT(false, "Failed to parse placejumps.json definitions file.");
                }
                
                // Populate menu with jump tions.
                for(std::vector<View::PlaceJumpModel>::iterator it = placeJumps.begin(); it != placeJumps.end(); it++)
                {
                    View::PlaceJumpModel& jump = *it;
                    optionsModel->AddItem(jump.GetName(),
                                          jump.GetName(), "", jump.GetIcon(),
                                          Eegeo_NEW(View::PlaceJumpMenuOption)(jump, Resolve<SettingsMenu::View::SettingsMenuViewModel>(), Resolve<ExampleAppMessaging::TMessageBus>(), Resolve<Metrics::IMetricsService>(), Resolve<Menu::View::IMenuReactionModel>()));
                }
            }
        }
    }
}
