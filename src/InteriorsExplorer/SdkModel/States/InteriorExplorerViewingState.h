// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IStateMachineState.h"
#include "InteriorExplorerState.h"
#include "InteriorsExplorer.h"
#include "Streaming.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace States
            {
                
                class InteriorExplorerViewingState : public Helpers::IStateMachineState
                {
                private:
                    
                    AppModes::States::SdkModel::InteriorExplorerState& m_parentState;
                    InteriorsExplorerModel& m_interiorExplorerModel;
                    Eegeo::Streaming::CameraFrustumStreamingVolume& m_cameraFrustumStreamingVolume;
                    Eegeo::Helpers::TCallback0<InteriorExplorerViewingState> m_exitCallback;
                    
                    bool m_exiting;
                    
                    void OnInteriorExplorerExit();
                    
                public:
                    
                    InteriorExplorerViewingState(AppModes::States::SdkModel::InteriorExplorerState& parentState,
                                                 InteriorsExplorerModel& interiorExplorerModel,
                                                 Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume);
                    
                    ~InteriorExplorerViewingState();
                    
                    void Enter();
                    
                    void Update(float dt);
                    
                    void Exit();
                };
            }
        }
    }
}