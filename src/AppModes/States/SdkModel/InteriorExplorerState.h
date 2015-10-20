// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IStateMachineState.h"
#include "AppCamera.h"
#include "StateMachine.h"
#include "Interiors.h"
#include "Streaming.h"
#include "InteriorsExplorer.h"
#include "ICallback.h"
#include <vector>
#include "AppModes.h"
#include "GlobeCamera.h"
#include "EegeoUI.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                namespace InteriorExplorerSubStates
                {
                    enum Values
                    {
                        Transition = 0,
                        Stream,
                        View,
                        Exit
                    };
                }
                
                class InteriorExplorerState : public Helpers::IStateMachineState
                {
                private:
                    
                    AppCamera::SdkModel::IAppCameraController& m_cameraController;
                    int m_interiorCameraHandle;
                    Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& m_worldCameraController;
                    ExampleApp::InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& m_interiorsCameraController;
                    Eegeo::UI::NativeUIFactories& m_nativeUIFactories;
                    Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<InteriorExplorerState> m_failAlertHandler;
                    
                    Eegeo::Resources::Interiors::InteriorController& m_interiorController;
                    
                    Helpers::StateMachine* m_pSubStateMachine;
                    std::vector<Helpers::IStateMachineState*> m_subStates;
                    
                    AppModes::SdkModel::IAppModeModel& m_appModeModel;
                    
                    void OnFailAlertBoxDismissed();
                
                public:
                    
                    InteriorExplorerState(AppCamera::SdkModel::IAppCameraController& cameraController,
                                          Eegeo::Resources::Interiors::InteriorController& interiorController,
                                          int interiorCameraHandle,
                                          Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                          InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                          InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                          AppModes::SdkModel::IAppModeModel& appModeModel,
                                          Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& worldCameraController,
                                          ExampleApp::InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& interiorsCameraController,
                                          Eegeo::UI::NativeUIFactories& nativeUIFactories);
                    
                    ~InteriorExplorerState();
                    
                    void Enter();
                    
                    void Update(float dt);
                    
                    void Exit();
                    
                    void SetSubState(InteriorExplorerSubStates::Values stateIndex);
                    
                    void ReturnToWorldMode();
                    
                    void ShowFailMessage();
                };
            }
        }
    }
}