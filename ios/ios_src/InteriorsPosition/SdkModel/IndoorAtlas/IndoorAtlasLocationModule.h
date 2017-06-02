// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "IndoorAtlasLocationController.h"
#include "IndoorAtlasLocationManager.h"
#include "IndoorAtlasLocationService.h"
#include "iOSAlertBoxFactory.h"
#include "ICallback.h"
#include "AppModeModel.h"
#include "InteriorsExplorer.h"
#include "ApplicationConfiguration.h"
#include "ILocationService.h"
#include "BidirectionalBus.h"


@class IndoorAtlasLocationManager;

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
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
                                              Eegeo::Location::ILocationService& defaultLocationService,
                                              Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository,
                                              Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory& iOSAlertBoxFactory,
                                              ExampleAppMessaging::TMessageBus& messageBu);
                    ~IndoorAtlasLocationModule();
            
                    IndoorAtlasLocationService& GetLocationService() { return *m_pLocationService; }
            
                private:
                    IndoorAtlasLocationController* m_pLocationController;
                    IndoorAtlasLocationService* m_pLocationService;
                    IndoorAtlasLocationManager* m_pLocationManager;
                };
            }
        }
    }
}
