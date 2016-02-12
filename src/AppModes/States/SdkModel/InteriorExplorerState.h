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
#include "MyPinCreation.h"
#include "Tours.h"

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
                    Eegeo::Helpers::TCallback0<InteriorExplorerState> m_tourStartedCallback;
                    Tours::SdkModel::ITourService& m_tourService;
                    Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& m_worldCameraController;
                    ExampleApp::InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& m_interiorsCameraController;
                    Eegeo::UI::NativeUIFactories& m_nativeUIFactories;
                    Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<InteriorExplorerState> m_failAlertHandler;
                    
                    Helpers::StateMachine* m_pSubStateMachine;
                    std::vector<Helpers::IStateMachineState*> m_subStates;
                    
                    AppModes::SdkModel::IAppModeModel& m_appModeModel;
                    
                    MyPinCreation::SdkModel::IMyPinCreationModel& m_myPinCreationModel;
                    InteriorsExplorer::SdkModel::InteriorExplorerUserInteractionModel& m_interiorExplorerUserInteractionModel;
                    
                    bool m_lastEntryAttemptSuccessful;
                    
                    void OnFailAlertBoxDismissed();
                    
                    void OnTourStarted();
                
                public:
                    
                    InteriorExplorerState(AppCamera::SdkModel::IAppCameraController& cameraController,
                                          Eegeo::Resources::Interiors::InteriorController& interiorController,
                                          int interiorCameraHandle,
                                          Tours::SdkModel::ITourService& tourService,
                                          Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                          InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                          InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                          InteriorsExplorer::SdkModel::InteriorExplorerUserInteractionModel& interiorExplorerUserInteractionModel,
                                          AppModes::SdkModel::IAppModeModel& appModeModel,
                                          Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& worldCameraController,
                                          ExampleApp::InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& interiorsCameraController,
                                          Eegeo::UI::NativeUIFactories& nativeUIFactories,
                                          MyPinCreation::SdkModel::IMyPinCreationModel& myPinCreationModel);
                    
                    ~InteriorExplorerState();
                    
                    void Enter(int previousState);
                    
                    void Update(float dt);
                    
                    void Exit(int nextState);
                    
                    void SetSubState(InteriorExplorerSubStates::Values stateIndex);
                    
                    void ReturnToWorldMode();
                    
                    void ShowFailMessage();
                    
                    void SetLastEntryAttemptSuccessful(bool successful);
                    
                    bool GetLastEntryAttemptSuccessful() const;
                };
            }
        }
    }
}