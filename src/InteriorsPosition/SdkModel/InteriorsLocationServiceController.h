// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once


#include "CurrentLocationService.h"
#include "InteriorsExplorer.h"
#include "ICameraTransitionController.h"
#include "Compass.h"
#include "CompassModeChangedMessage.h"
#include "AppModes.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            class InteriorsLocationServiceController
            {
            public:
                InteriorsLocationServiceController(Eegeo::Helpers::CurrentLocationService::CurrentLocationService& currentLocationService,
                                                   Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                   Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                   InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                                   Compass::SdkModel::ICompassModel& compassModel,
                                                   AppModes::SdkModel::IAppModeModel& appModeModel);
                
                ~InteriorsLocationServiceController();
                
                void Update();
                
            private:
                Eegeo::Helpers::CurrentLocationService::CurrentLocationService& m_currentLocationService;
                
                Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                
                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;

                InteriorsExplorer::SdkModel::InteriorsExplorerModel& m_interiorsExplorerModel;
                
                Compass::SdkModel::ICompassModel& m_compassModel;

                AppModes::SdkModel::IAppModeModel& m_appModeModel;
            };
        }
    }
}
