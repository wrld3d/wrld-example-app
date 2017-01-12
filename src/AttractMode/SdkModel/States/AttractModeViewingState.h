// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "AppModes.h"
#include "CameraSplinePlaybackController.h"
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
                    Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController& m_cameraSplinePlaybackController;
                    
                public:
                    AttractModeViewingState(Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController& cameraSplinePlaybackController);

                    void Enter(int previousState);
                    void Update(float dt);
                    void Exit(int nextState);
                };
            }
        }
    }
}
