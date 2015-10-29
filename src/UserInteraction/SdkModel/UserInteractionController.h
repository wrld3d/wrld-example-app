// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

// eeGeo SDK includes
#include "ICallback.h"
#include "Types.h"
// App includes
#include "AppCamera.h"
#include "ICameraTransitionController.h"
#include "UserInteraction.h"

namespace ExampleApp
{
    namespace UserInteraction
    {
        namespace SdkModel
        {
            class UserInteractionController : Eegeo::NonCopyable
            {
            private:
                UserInteractionModel& m_userInteractionModel;
                AppCamera::SdkModel::IAppCameraController& m_appCameraController;
                CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;
                Eegeo::Helpers::TCallback0<UserInteractionController> m_cameraTransitionChangedHandler;
                
            public:
                UserInteractionController(UserInteractionModel& userInteractionModel,
                                          AppCamera::SdkModel::IAppCameraController& appCameraController,
                                          CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController);
                
                ~UserInteractionController();
                
            private:
                void OnCameraTransitionChanged();
            };
        }
    }
}

