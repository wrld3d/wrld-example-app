// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Hypodermic/ContainerBuilder.h"

namespace ExampleApp
{
    namespace UserInteraction
    {
        namespace SdkModel
        {
            class UserInteractionModule
            {
            public:
                void Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder);
            };
            
            /*
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
            };*/
        }
    }
}