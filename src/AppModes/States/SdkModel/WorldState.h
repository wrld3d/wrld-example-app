// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IStateMachineState.h"
#include "AppCamera.h"
#include "AppModes.h"
#include "Tours.h"
#include "ICallback.h"
#include "Interiors.h"
#include "InteriorsExplorer.h"

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
                    
                    AppModes::SdkModel::IAppModeModel& m_appModeModel;
                    
                    ExampleApp::InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& m_interiorsCameraController;
                    
                    Eegeo::Helpers::TCallback0<WorldState> m_tourStartedCallback;
                    Tours::SdkModel::ITourService& m_tourService;
                    void OnTourStarted();
                    
                    Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                    Eegeo::Helpers::TCallback1<WorldState, const Eegeo::Resources::Interiors::InteriorId> m_interiorSelectionModelChangedCallback;
                    void OnInteriorSelectionModelChanged(const Eegeo::Resources::Interiors::InteriorId& interiorId);
                    
                public:
                    
                    WorldState(AppCamera::SdkModel::IAppCameraController& cameraController,
                               int worldCameraHandle,
                               Tours::SdkModel::ITourService& tourService,
                               Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                               AppModes::SdkModel::IAppModeModel& appModeModel,
                               ExampleApp::InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& interiorsCameraController);
                    
                    ~WorldState();
                    
                    void Enter();
                    
                    void Update(float dt);
                    
                    void Exit();
                };
            }
        }
    }
}