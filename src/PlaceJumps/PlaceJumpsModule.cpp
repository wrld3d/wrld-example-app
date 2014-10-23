// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <vector>
#include <string>
#include <fstream>
#include "PlaceJumpsModule.h"
#include "PlaceJumpsDataParser.h"
#include "PlaceJumpsModel.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "PlaceJumpMenuOption.h"
#include "PlaceJumpController.h"
#include "GpsGlobeCameraController.h"

namespace ExampleApp
{
    namespace PlaceJumps
    {
        PlaceJumpsModule::PlaceJumpsModule(Eegeo::Helpers::IFileIO& fileIO,
                                           Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& controller,
                                           Compass::ICompassModel& compassModel,
                                           ExampleApp::Menu::IMenuViewModel& menuViewModel)
        {
            m_pJumpController = Eegeo_NEW(PlaceJumpController)(controller, compassModel);
            
            m_pMenuModel = Eegeo_NEW(Menu::MenuModel)();
            m_pMenuOptionsModel = Eegeo_NEW(Menu::MenuOptionsModel)(*m_pMenuModel);
            
            std::fstream stream;
            size_t size;
            
            if(!fileIO.OpenFile(stream, size, "placejumps.json"))
            {
                Eegeo_ASSERT(false, "Failed to load placejumps.json definitions file.");
            }
            
            std::string json((std::istreambuf_iterator<char>(stream)),
                             (std::istreambuf_iterator<char>()));
            
            std::vector<PlaceJumpModel> placeJumps;
            if(!PlaceJumpsDataParser::ParsePlaceJumps(json, placeJumps))
            {
                Eegeo_ASSERT(false, "Failed to parse placejumps.json definitions file.");
            }
            
            // Populate menu with jump tions.
            for(std::vector<PlaceJumpModel>::iterator it = placeJumps.begin(); it != placeJumps.end(); it++)
            {
                PlaceJumpModel& jump = *it;
                m_pMenuOptionsModel->AddItem(jump.GetName(),
                                             jump.GetName(), "", jump.GetIcon(),
                                             Eegeo_NEW(PlaceJumpMenuOption)(jump, *m_pJumpController, menuViewModel));
            }
        }
        
        PlaceJumpsModule::~PlaceJumpsModule()
        {
            Eegeo_DELETE m_pMenuOptionsModel;
            Eegeo_DELETE m_pMenuModel;
            Eegeo_DELETE m_pJumpController;
        }
    }
}
