// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "IndoorAtlasLocationManager.h"
#include "ICallback.h"
#include "AppModeModel.h"
#include "InteriorsExplorer.h"
#include "ApplicationConfiguration.h"

namespace ExampleApp
{
    namespace IndoorAtlas
    {
        class IndoorAtlasLocationController
        {
        public:
            IndoorAtlasLocationController(IndoorAtlasLocationService& locationService,
                                          IndoorAtlasLocationManager& locationManager,
                                          ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                          Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                          const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                          const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration);
            ~IndoorAtlasLocationController();
            
        private:
            IndoorAtlasLocationService& m_locationService;
            IndoorAtlasLocationManager& m_locationManager;
            
            ExampleApp::AppModes::SdkModel::IAppModeModel& m_appModeModel;
            Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
            const Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
            const ExampleApp::ApplicationConfig::ApplicationConfiguration& m_applicationConfiguration;
            
            Eegeo::Helpers::TCallback0<IndoorAtlasLocationController> m_floorSelectedCallback;
            Eegeo::Helpers::TCallback0<IndoorAtlasLocationController> m_appModeChangedCallback;
            
            void OnAppModeChanged();
            void OnFloorSelected();
        };
    }
}