// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "IndoorAtlasLocationManager.h"
#include "ICallback.h"
#include "AppModeModel.h"
#include "InteriorsExplorer.h"
#include "ApplicationConfiguration.h"
#include "InteriorMetaDataRepository.h"
#include "ApplicationInteriorTrackingInfo.h"

namespace ExampleApp
{
    namespace IndoorAtlas
    {
        class IndoorAtlasLocationController
        {
        public:
            IndoorAtlasLocationController(IndoorAtlasLocationManager& locationManager,
                                          ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                          const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                          Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository);
            ~IndoorAtlasLocationController();
            
        private:
            IndoorAtlasLocationManager& m_locationManager;
            
            ExampleApp::AppModes::SdkModel::IAppModeModel& m_appModeModel;
            const Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
            
            Eegeo::Helpers::TCallback0<IndoorAtlasLocationController> m_appModeChangedCallback;
            
            void OnAppModeChanged();
            
            Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& m_interiorMetaDataRepository;
        };
    }
}
