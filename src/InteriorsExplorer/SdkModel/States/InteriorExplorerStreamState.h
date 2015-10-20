// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IStateMachineState.h"
#include "InteriorExplorerState.h"
#include "AppCamera.h"
#include "Interiors.h"
#include "Streaming.h"
#include "ICallback.h"
#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace States
            {
                
                    class InteriorExplorerStreamState : public Helpers::IStateMachineState
                    {
                    private:
                        
                        Eegeo::Resources::Interiors::InteriorController& m_interiorController;
                        Eegeo::Streaming::CameraFrustumStreamingVolume& m_cameraFrustumStreamingVolume;
                        InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& m_interiorVisibilityUpdater;
                        
                        AppModes::States::SdkModel::InteriorExplorerState& m_parentState;
                        
                        const float m_maxTimeout;
                        float m_timeUntilTimeout;
                        
                    public:
                        
                        InteriorExplorerStreamState(AppModes::States::SdkModel::InteriorExplorerState& parentState,
                                                    Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                    Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                                    InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater);
                        
                        ~InteriorExplorerStreamState();
                        
                        void Enter();
                        
                        void Update(float dt);
                        
                        void Exit();
                    };
            }
        }
    }
}