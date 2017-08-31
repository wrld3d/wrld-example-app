// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once


#include "CurrentLocationService.h"
#include "InteriorsExplorerModel.h"
#include "ICameraTransitionController.h"
#include "Compass.h"
#include "CompassModeChangedMessage.h"

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
                                                   CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                   Compass::SdkModel::ICompassModel& compassModel,
                                                   float locationDistance);

                InteriorsLocationServiceController(Eegeo::Helpers::CurrentLocationService::CurrentLocationService& currentLocationService,
                                                    Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                    CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                    Compass::SdkModel::ICompassModel& compassModel);

                ~InteriorsLocationServiceController();
                
                void Update();
                
            private:
                Eegeo::Helpers::CurrentLocationService::CurrentLocationService& m_currentLocationService;
                
                Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                
                CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;
                
                Compass::SdkModel::ICompassModel& m_compassModel;

                bool m_hasLocationDistance;

                float m_locationDistance;
            };
        }
    }
}
