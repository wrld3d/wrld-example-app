// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IStateMachineState.h"
#include "AppCamera.h"
#include "AppModes.h"
#include "Tours.h"
#include "ICallback.h"
#include "Interiors.h"
#include "InteriorsExplorer.h"
#include "AttractModeTimer.h"
#include "IUserIdleService.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                class WorldState : public Helpers::IStateMachineState
                {
                private:
                    
                    AppCamera::SdkModel::IAppCameraController& m_cameraController;
                    int m_worldCameraHandle;
                    
                public:
                    
                    WorldState(AppCamera::SdkModel::IAppCameraController& cameraController,
                               int worldCameraHandle);
                    
                    ~WorldState();
                    
                    void Enter(int previousState);
                    
                    void Update(float dt);
                    
                    void Exit(int nextState);
                };
            }
        }
    }
}
