// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "CameraSplinePlaybackController.h"
#include "IAppModeModel.h"
#include "IUserIdleService.h"
#include "StateMachine.h"

namespace ExampleApp
{
    namespace AttractMode
    {
        namespace SdkModel
        {
            namespace States
            {
                class AttractModeViewingState : public Helpers::IStateMachineState
                {
                private:
                    long long m_idleTimeAtStartMs;
                    AppModes::SdkModel::IAppModeModel& m_appModeModel;
                    Eegeo::Input::IUserIdleService& m_userIdleService;
                    Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController& m_cameraSplinePlaybackController;
                    
                public:
                    AttractModeViewingState(AppModes::SdkModel::IAppModeModel& appModeModel,
                                            Eegeo::Input::IUserIdleService& userIdleService,
                                            Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController& cameraSplinePlaybackController);

                    void Enter(int previousState);
                    void Update(float dt);
                    void Exit(int nextState);
                };
            }
        }
    }
}
