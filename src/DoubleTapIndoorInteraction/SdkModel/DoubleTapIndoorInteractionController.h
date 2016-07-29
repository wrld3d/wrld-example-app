// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Interiors.h"
#include "IRayCaster.h"
#include "EnvironmentRayCaster.h"
#include "ICameraTransitionController.h"
#include "IDoubleTapIndoorInteractionController.h"



namespace ExampleApp
{
    namespace DoubleTapIndoorInteraction
    {
        namespace SdkModel
        {
            
            class DoubleTapIndoorInteractionController : public IDoubleTapIndoorInteractionController {
            
                
            public:
                
                DoubleTapIndoorInteractionController(Eegeo::Resources::Interiors::InteriorsCameraController& interiorsCameraController,
                                                     ExampleApp::CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                     Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                     Eegeo::Collision::IRayCaster& rayCaster);
                ~DoubleTapIndoorInteractionController();
                void OnDoubleTap(const AppInterface::TapData& data);
                
            private:
                
                Eegeo::Collision::IRayCaster& m_enovRayCaster;
                Eegeo::Resources::Interiors::InteriorsCameraController& m_interiorsCameraController;
                Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                ExampleApp::CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;
                
                void ZoomInTo(float distance,const AppInterface::TapData& data);

            };
            
        }
    }
}