// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "IndoorAtlasLocationController.h"
#include "IndoorAtlasLocationManager.h"
#include "IndoorAtlasLocationService.h"
#include "ICallback.h"
#include "AppModeModel.h"
#include "InteriorsExplorer.h"
#include "ApplicationConfiguration.h"
#include "ILocationService.h"
#include "AndroidNativeState.h"

class IndoorAtlasLocationManager;

namespace ExampleApp
{
    namespace IndoorAtlas
    {
        class IndoorAtlasLocationModule
        {
        public:
            IndoorAtlasLocationModule(ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                      Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                      const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                      const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                      const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
                                      Eegeo::Location::ILocationService& defaultLocationService,
									  AndroidNativeState& nativeState);
            ~IndoorAtlasLocationModule();
            
            IndoorAtlasLocationService& GetLocationService() { return *m_pLocationService; }
            
        private:
            IndoorAtlasLocationController* m_pLocationController;
            IndoorAtlasLocationService* m_pLocationService;
            IndoorAtlasLocationManager* m_pLocationManager;
        };
    }
}
