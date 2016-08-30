// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Interiors.h"
#include "Types.h"
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
            class DoubleTapIndoorInteractionController : public IDoubleTapIndoorInteractionController, private Eegeo::NonCopyable
            {
            public:
                DoubleTapIndoorInteractionController(const std::shared_ptr<Eegeo::Resources::Interiors::InteriorsCameraController>& interiorsCameraController,
                                                     const std::shared_ptr<ExampleApp::CameraTransitions::SdkModel::ICameraTransitionController>& cameraTransitionController,
                                                     const std::shared_ptr<Eegeo::Resources::Interiors::InteriorInteractionModel>& interiorInteractionModel,
                                                     const std::shared_ptr<Eegeo::Collision::IRayCaster>& rayCaster);
                ~DoubleTapIndoorInteractionController();
                void OnDoubleTap(const AppInterface::TapData& data);
                
            private:
                
                const std::shared_ptr<Eegeo::Collision::IRayCaster> m_enovRayCaster;
                const std::shared_ptr<Eegeo::Resources::Interiors::InteriorsCameraController> m_interiorsCameraController;
                const std::shared_ptr<Eegeo::Resources::Interiors::InteriorInteractionModel> m_interiorInteractionModel;
                const std::shared_ptr<ExampleApp::CameraTransitions::SdkModel::ICameraTransitionController> m_cameraTransitionController;
                
                void ZoomInTo(float distance, const AppInterface::TapData& data);
            };
            
        }
    }
}