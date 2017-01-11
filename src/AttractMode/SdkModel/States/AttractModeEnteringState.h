// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "IAppCameraController.h"
#include "IStateMachineState.h"
#include "StateMachine.h"

namespace ExampleApp
{
    namespace AttractMode
    {
        namespace SdkModel
        {
            namespace States
            {
                class AttractModeEnteringState : public Helpers::IStateMachineState
                {
                private:
                    Helpers::StateMachine& m_stateMachine;
                    AppCamera::SdkModel::IAppCameraController& m_cameraController;
                    const int m_attractModeCameraHandle;
                    
                public:
                    AttractModeEnteringState(Helpers::StateMachine& stateMachine,
                                             AppCamera::SdkModel::IAppCameraController& cameraController,
                                             const int attractModeCameraHandle);

                    void Enter(int previousState);
                    void Update(float dt);
                    void Exit(int nextState);
                };
            }
        }
    }
}
