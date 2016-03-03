// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IStateMachineState.h"
#include "InteriorExplorerState.h"
#include "InteriorsExplorer.h"
#include "Streaming.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace States
            {
                
                class InteriorExplorerExitingState : public Helpers::IStateMachineState
                {
                private:
                    
                    AppModes::States::SdkModel::InteriorExplorerState& m_parentState;
                    Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                    Eegeo::Streaming::CameraFrustumStreamingVolume& m_cameraFrustumStreamingVolume;
                    InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& m_interiorVisibilityUpdater;
                    InteriorsExplorerModel& m_interiorsExplorerModel;
                    
                    void OnInteriorExplorerExit();
                    
                public:
                    
                    InteriorExplorerExitingState(AppModes::States::SdkModel::InteriorExplorerState& parentState,
                                                 Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                 Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                                 InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                                 InteriorsExplorerModel& interiorsExplorerModel);
                    
                    ~InteriorExplorerExitingState();
                    
                    void Enter(int previousState);
                    
                    void Update(float dt);
                    
                    void Exit(int nextState);
                };
            }
        }
    }
}