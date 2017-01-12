// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "AppModes.h"
#include "IAppCameraController.h"
#include "IStateMachineState.h"

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
                    AppModes::States::SdkModel::AttractState& m_attractState;
                    AppCamera::SdkModel::IAppCameraController& m_cameraController;
                    const int m_attractModeCameraHandle;
                    
                public:
                    AttractModeEnteringState(AppModes::States::SdkModel::AttractState& attractState,
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
