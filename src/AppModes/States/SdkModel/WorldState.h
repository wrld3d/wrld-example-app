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
#include "CameraFrustumStreamingVolume.h"

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
                    Eegeo::Streaming::CameraFrustumStreamingVolume& m_cameraFrustumStreamingVolume;
                    Eegeo::Helpers::TCallback0<WorldState> m_transitionInFlightCallback;
                    
                    void OnTransitionInFlight();
                    
                public:
                    
                    WorldState(AppCamera::SdkModel::IAppCameraController& cameraController,
                               int worldCameraHandle,
                               Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume);
                    
                    ~WorldState();
                    
                    void Enter(int previousState);
                    
                    void Update(float dt);
                    
                    void Exit(int nextState);
                };
            }
        }
    }
}
