// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IStateMachineState.h"
#include "InteriorExplorerState.h"
#include "AppCamera.h"
#include "Interiors.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace States
            {
                class InteriorExplorerSetupState : public Helpers::IStateMachineState
                {
                private:
                    
                    AppCamera::SdkModel::IAppCameraController& m_cameraController;
                    int m_interiorCameraHandle;
                    
                    AppModes::States::SdkModel::InteriorExplorerState& m_parentState;
                    
                public:
                    
                    InteriorExplorerSetupState(AppModes::States::SdkModel::InteriorExplorerState& parentState,
                                               AppCamera::SdkModel::IAppCameraController& cameraController,
                                               int interiorCameraHandle);
                    
                    ~InteriorExplorerSetupState();
                    
                    void Enter();
                    
                    void Update(float dt);
                    
                    void Exit();
                };
            }
        }
    }
}