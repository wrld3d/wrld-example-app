// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "AppModeModel.h"
#include "ApplicationConfiguration.h"
#include "ICallback.h"
#include "ILocationService.h"
#include "InteriorsExplorer.h"
#include "SenionLabLocationController.h"
#include "SenionLabLocationInterop.h"
#include "SenionLabLocationService.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                class SenionLabLocationModule : protected Eegeo::NonCopyable
                {
                public:
                    SenionLabLocationModule(ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                            Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                            const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                            const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                            Eegeo::Location::ILocationService& defaultLocationService,
                                            Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository,
                                            ExampleAppMessaging::TMessageBus& messageBus,
                                            AndroidNativeState& nativeState);
                    ~SenionLabLocationModule();
                    
                    SenionLabLocationService& GetLocationService();
                    SenionLabLocationInterop& GetLocationManager();

                private:
                    SenionLabLocationInterop* m_pLocationInterop;
                    SenionLabLocationService* m_pLocationService;
                    SenionLabLocationController* m_pLocationController;
                };
            }
        }
    }
}
