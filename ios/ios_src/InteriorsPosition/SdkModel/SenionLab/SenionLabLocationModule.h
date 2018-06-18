// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "SenionLabIncludes.h"
#include "ICallback.h"
#include "AppModeModel.h"
#include "InteriorsExplorer.h"
#include "ApplicationConfiguration.h"
#include "ILocationService.h"
#include "InteriorMetaData.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                class SenionLabLocationInterop;
                
                class SenionLabLocationModule
                {
                public:
                    SenionLabLocationModule(ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                            Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                            const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                            const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                            Eegeo::Location::ILocationService& defaultLocationService,
                                            Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository,
                                            ExampleAppMessaging::TMessageBus& messageBus);
                    ~SenionLabLocationModule();
                    
                    InteriorsPosition::SdkModel::SenionLab::SenionLabLocationService& GetLocationService() const;
                    
                private:
                    InteriorsPosition::SdkModel::SenionLab::SenionLabLocationInterop* m_pSenionInterop;
                    InteriorsPosition::SdkModel::SenionLab::SenionLabLocationService* m_pLocationService;
                    InteriorsPosition::SdkModel::SenionLab::SenionLabLocationController* m_pLocationController;
                };
            }
        }
    }
}
