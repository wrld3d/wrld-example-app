// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "SenionLabLocationController.h"
#include "SenionLabLocationManagerInterop.h"
#include "SenionLabLocationService.h"
#include "iOSAlertBoxFactory.h"
#include "ICallback.h"
#include "AppModeModel.h"
#include "InteriorsExplorer.h"
#include "ApplicationConfiguration.h"
#include "ILocationService.h"

@class SenionLabLocationManager;

namespace ExampleApp
{
    namespace SenionLab
    {
        class SenionLabLocationModule
        {
        public:
            SenionLabLocationModule(ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                    Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                    const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                    const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                    Eegeo::Location::ILocationService& defaultLocationService,
                                    Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository,
                                    Eegeo::UI::NativeAlerts::iOS::iOSAlertBoxFactory& iOSAlertBoxFactory,
                                    ExampleAppMessaging::TMessageBus& messageBus);
            ~SenionLabLocationModule();
            
            InteriorsPosition::SdkModel::SenionLab::SenionLabLocationService& GetLocationService() { return m_locationService; }
            
        private:
            InteriorsPosition::SdkModel::SenionLab::SenionLabLocationService m_locationService;
            SenionLabLocationManagerInterop m_locationManager;
            InteriorsPosition::SdkModel::SenionLab::SenionLabLocationController m_locationController;
        };
    }
}
