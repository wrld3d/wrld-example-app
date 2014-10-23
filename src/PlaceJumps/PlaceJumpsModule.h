// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Menu.h"
#include "IPlaceJumpsModule.h"
#include "Types.h"
#include "PlaceJumps.h"
#include "PlaceJumpsDataParser.h"
#include "IFileIO.h"
#include "GlobeCamera.h"
#include "Compass.h"

namespace ExampleApp
{
    namespace PlaceJumps
    {

        class PlaceJumpsModule : public IPlaceJumpsModule, private Eegeo::NonCopyable
        {
        public:
            
            PlaceJumpsModule(Eegeo::Helpers::IFileIO& fileIO,
                             Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& camera,
                             Compass::ICompassModel& compassModel,
                             ExampleApp::Menu::IMenuViewModel& menuViewModel);
            
            ~PlaceJumpsModule();
            
            Menu::IMenuModel& GetPlaceJumpsMenuModel() const { return *m_pMenuModel; }
            IPlaceJumpController& GetPlaceJumpController() const { return *m_pJumpController; }
            
        private:
            
            Menu::IMenuModel* m_pMenuModel;
            Menu::IMenuOptionsModel* m_pMenuOptionsModel;
            IPlaceJumpController* m_pJumpController;
        };
    }
}
