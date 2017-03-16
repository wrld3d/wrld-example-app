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
                    Eegeo::Resources::Interiors::InteriorsCameraController& m_interiorsCameraController;
                    InteriorsExplorer::SdkModel::InteriorsExplorerModel& m_interiorsExplorerModel;
                    Eegeo::UI::NativeUIFactories& m_nativeUIFactories;
                    Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<InteriorExplorerState> m_failAlertHandler;
                    
                    Helpers::StateMachine* m_pSubStateMachine;
                    std::vector<Helpers::IStateMachineState*> m_subStates;
                    
                    AppModes::SdkModel::IAppModeModel& m_appModeModel;
                    
                    InteriorsExplorer::SdkModel::InteriorExplorerUserInteractionModel& m_interiorExplorerUserInteractionModel;
                    
                    void OnFailAlertBoxDismissed();
                    
                public:
                    
                    InteriorExplorerState(AppCamera::SdkModel::IAppCameraController& cameraController,
                                          Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                          Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                          int interiorCameraHandle,
                                          Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                          InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                          InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                          InteriorsExplorer::SdkModel::InteriorExplorerUserInteractionModel& interiorExplorerUserInteractionModel,
                                          AppModes::SdkModel::IAppModeModel& appModeModel,
                                          Eegeo::Resources::Interiors::InteriorsCameraController& interiorsCameraController,
                                          Eegeo::UI::NativeUIFactories& nativeUIFactories);
                    
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
