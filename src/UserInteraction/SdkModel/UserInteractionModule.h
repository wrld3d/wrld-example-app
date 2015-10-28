// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

// eeGeo SDK includes
#include "Types.h"
// App includes
#include "AppCamera.h"
#include "ICameraTransitionController.h"
#include "UserInteraction.h"

//TODO: Add Observer after implementing

namespace ExampleApp
{
    namespace UserInteraction
    {
        namespace SdkModel
        {
            class UserInteractionModule : Eegeo::NonCopyable
            {
            private:
                UserInteractionModel* m_pUserInteractionModel;
                UserInteractionController* m_pUserInteractionController;
                
            public:
                UserInteractionModule(AppCamera::SdkModel::IAppCameraController& appCameraController,
                                      CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController);
                
                ~UserInteractionModule();
            };
        }
    }
}