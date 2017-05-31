// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "IIndoorAtlasLocationManager.h"
#include "ICallback.h"
#include "AppModeModel.h"
#include "InteriorsExplorer.h"
#include "ApplicationConfiguration.h"
#include "InteriorMetaDataRepository.h"
#include "ApplicationInteriorTrackingInfo.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace IndoorAtlas
            {
                class IndoorAtlasLocationController
                {
                public:
                	IndoorAtlasLocationController(IIndoorAtlasLocationManager& locationManager,
                                                  AppModes::SdkModel::IAppModeModel& appModeModel,
                                                  const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                  Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository,
                                                  ExampleAppMessaging::TMessageBus& messageBus);
                    ~IndoorAtlasLocationController();
                    
                private:
                    IIndoorAtlasLocationManager& m_locationManager;
                    ExampleApp::AppModes::SdkModel::IAppModeModel& m_appModeModel;
                    const Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                    Eegeo::Helpers::TCallback0<IndoorAtlasLocationController> m_appModeChangedCallback;
                    Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& m_interiorMetaDataRepository;
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    
                    void OnAppModeChanged();
                };
            }
        }
    }
}
