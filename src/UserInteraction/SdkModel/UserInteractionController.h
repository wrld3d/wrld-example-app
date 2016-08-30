// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "Types.h"
#include "AppCamera.h"
#include "ICameraTransitionController.h"
#include "InteriorsExplorer.h"
#include "UserInteraction.h"
#include <memory>

namespace ExampleApp
{
    namespace UserInteraction
    {
        namespace SdkModel
        {
            class UserInteractionController : Eegeo::NonCopyable
            {
            private:
                const std::shared_ptr<UserInteractionModel> m_userInteractionModel;
                const std::shared_ptr<AppCamera::SdkModel::IAppCameraController> m_appCameraController;
                const std::shared_ptr<CameraTransitions::SdkModel::ICameraTransitionController> m_cameraTransitionController;
                const std::shared_ptr<InteriorsExplorer::SdkModel::InteriorExplorerUserInteractionModel> m_interiorExplorerUserInteractionModel;
                Eegeo::Helpers::TCallback0<UserInteractionController> m_handler;
                
            public:
                UserInteractionController(const std::shared_ptr<UserInteractionModel>& userInteractionModel,
                                          const std::shared_ptr<AppCamera::SdkModel::IAppCameraController>& appCameraController,
                                          const std::shared_ptr<InteriorsExplorer::SdkModel::InteriorExplorerUserInteractionModel>& interiorExplorerUserInteractionModel,
                                          const std::shared_ptr<CameraTransitions::SdkModel::ICameraTransitionController>& cameraTransitionController);
                
                ~UserInteractionController();
                
            private:
                void OnObservedChanged();
            };
        }
    }
}

