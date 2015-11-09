// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

// eeGeo SDK includes
#include "Types.h"
// App includes
#include "AppCamera.h"
#include "BidirectionalBus.h"
#include "ICameraTransitionController.h"
#include "InteriorsExplorer.h"
#include "UserInteraction.h"

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
                UserInteractionEnabledObserver* m_pUserInteractionEnabledObserver;
                
            public:
                UserInteractionModule(AppCamera::SdkModel::IAppCameraController& appCameraController,
                                      CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                      InteriorsExplorer::SdkModel::InteriorExplorerUserInteractionModel& interiorExplorerUserInteractionModel,
                                      ExampleAppMessaging::TMessageBus& messageBus);
                
                ~UserInteractionModule();
                
                const UserInteractionModel& GetUserInteractionModel() const;
            };
        }
    }
}