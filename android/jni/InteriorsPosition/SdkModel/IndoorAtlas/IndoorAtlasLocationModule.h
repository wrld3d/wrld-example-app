// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "AppModeModel.h"
#include "ApplicationConfiguration.h"
#include "ICallback.h"
#include "ILocationService.h"
#include "InteriorsExplorer.h"
#include "IndoorAtlasLocationController.h"
#include "IndoorAtlasLocationInterop.h"
#include "IndoorAtlasLocationService.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace IndoorAtlas
            {
                class IndoorAtlasLocationModule : protected Eegeo::NonCopyable
                {
                public:
                    IndoorAtlasLocationModule(ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                              Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                              const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                              const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                              Eegeo::Location::ILocationService& defaultLocationService,
                                              Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository,
											  ExampleAppMessaging::TMessageBus& messageBus,
                                              AndroidNativeState& nativeState);
                    ~IndoorAtlasLocationModule();
                    
                    IndoorAtlasLocationService& GetLocationService();
                    IndoorAtlasLocationInterop& GetLocationManager();

                private:
                    IndoorAtlasLocationService* m_pLocationService;
                    IndoorAtlasLocationInterop* m_pLocationInterop;
                    IndoorAtlasLocationController* m_pLocationController;
                };
            }
        }
    }
}
