// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "InteriorsLocationServiceController.h"
#include "InteriorsLocationServiceProvider.h"
#include "CurrentLocationService.h"
#include "InteriorsExplorerModel.h"
#include "ICameraTransitionController.h"
#include "Compass.h"
#include "CompassModeChangedMessage.h"
#include "InteriorMetaDataRepository.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            class InteriorsLocationServiceModule
            {
            public:
                InteriorsLocationServiceModule(std::map<std::string, ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo> trackingInfoMap,
                                               InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                               Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                               Eegeo::Helpers::CurrentLocationService::CurrentLocationService& currentLocationService,
                                               Eegeo::Location::ILocationService& defaultLocationService,
                                               std::map<std::string, Eegeo::Location::ILocationService&> interiorLocationServices,
                                               Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository,
                                               Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                               CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                               Compass::SdkModel::ICompassModel& compassModel,
                                               ExampleAppMessaging::TMessageBus& messageBus);
                
                ~InteriorsLocationServiceModule();
                
                InteriorsLocationServiceController& GetController() { return *m_pController; }
                InteriorsLocationServiceProvider& GetProvider() { return *m_pProvider; }
                
            private:
                InteriorsLocationServiceController* m_pController;
                InteriorsLocationServiceProvider* m_pProvider;
            };
        }
    }
}
