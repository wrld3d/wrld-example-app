// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

// eeGeo SDK includes
#include "ICallback.h"
#include "Types.h"
// App includes
#include "AppCamera.h"
#include "ICameraTransitionController.h"
#include "InteriorsExplorer.h"
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
                InteriorsExplorer::SdkModel::InteriorExplorerUserInteractionModel& m_interiorExplorerUserInteractionModel;
                Eegeo::Helpers::TCallback0<UserInteractionController> m_handler;
                
            public:
                UserInteractionController(UserInteractionModel& userInteractionModel,
                                          AppCamera::SdkModel::IAppCameraController& appCameraController,
                                          InteriorsExplorer::SdkModel::InteriorExplorerUserInteractionModel& interiorExplorerUserInteractionModel,
                                          CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController);
                
                ~UserInteractionController();
                
            private:
                void OnObservedChanged();
            };
        }
    }
}

