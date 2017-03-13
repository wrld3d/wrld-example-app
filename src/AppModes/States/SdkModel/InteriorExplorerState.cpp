// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorExplorerState.h"
#include "IAppCameraController.h"
#include "InteriorExplorerSetupState.h"
#include "InteriorExplorerStreamState.h"
#include "InteriorExplorerViewingState.h"
#include "InteriorExplorerExitingState.h"
#include "InteriorSelectionModel.h"
#include "IAppModeModel.h"
#include "InteriorsCameraController.h"
#include "GpsGlobeCameraController.h"
#include "GlobeCameraController.h"
#include "CameraHelpers.h"
#include "EcefTangentBasis.h"
#include "NativeUIFactories.h"
#include "IAlertBoxFactory.h"
#include "LatLongAltitude.h"
#include "MyPinCreationModel.h"
#include "MyPinCreationStage.h"
#include "InteriorExplorerUserInteractionModel.h"
#include "InteriorsExplorerModel.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                InteriorExplorerState::InteriorExplorerState(AppCamera::SdkModel::IAppCameraController& cameraController,
                                                             Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                             Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                             int interiorCameraHandle,
                                                             Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                                             InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                                             InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                                             InteriorsExplorer::SdkModel::InteriorExplorerUserInteractionModel& interiorExplorerUserInteractionModel,
                                                             AppModes::SdkModel::IAppModeModel& appModeModel,
                                                             Eegeo::Resources::Interiors::InteriorsCameraController& interiorsCameraController,
                                                             Eegeo::UI::NativeUIFactories& nativeUIFactories)
                : m_interiorExplorerUserInteractionModel(interiorExplorerUserInteractionModel)
                , m_appModeModel(appModeModel)
                , m_interiorsCameraController(interiorsCameraController)
                , m_interiorsExplorerModel(interiorsExplorerModel)
                , m_nativeUIFactories(nativeUIFactories)
                , m_failAlertHandler(this, &InteriorExplorerState::OnFailAlertBoxDismissed)
                {
                    
                    m_subStates.push_back(Eegeo_NEW(InteriorsExplorer::SdkModel::States::InteriorExplorerSetupState)(*this,
                                                                                                                     cameraController,
                                                                                                                     interiorCameraHandle));
                    
                    m_subStates.push_back(Eegeo_NEW(InteriorsExplorer::SdkModel::States::InteriorExplorerStreamState)(*this,
                                                                                                                      interiorInteractionModel,
                                                                                                                      cameraFrustumStreamingVolume,
                                                                                                                      interiorVisibilityUpdater));
                    
                    m_subStates.push_back(Eegeo_NEW(InteriorsExplorer::SdkModel::States::InteriorExplorerViewingState)(*this,
                                                                                                                       interiorsExplorerModel,
                                                                                                                       interiorExplorerUserInteractionModel));
                    
                    m_subStates.push_back(Eegeo_NEW(InteriorsExplorer::SdkModel::States::InteriorExplorerExitingState)(*this,
                                                                                                                       interiorSelectionModel,
                                                                                                                       cameraFrustumStreamingVolume,
                                                                                                                       interiorVisibilityUpdater,
                                                                                                                       interiorsExplorerModel
                                                                                                                       ));
                    
                    m_pSubStateMachine = Eegeo_NEW(Helpers::StateMachine)(m_subStates);
                }
                
                InteriorExplorerState::~InteriorExplorerState()
                {
                    if(m_pSubStateMachine->GetCurrentStateIndex() >= 0)
                    {
                        m_pSubStateMachine->StopStateMachine();
                    }
                    
                    Eegeo_DELETE m_pSubStateMachine;
                    m_pSubStateMachine = NULL;
                    
                    for(int i = 0; i < m_subStates.size(); ++i)
                    {
                        Eegeo_DELETE m_subStates[i];
                    }
                    
                    m_subStates.clear();
                }
                
                void InteriorExplorerState::Enter(int previousState)
                {
                    m_interiorExplorerUserInteractionModel.SetEnabled(false);
                    m_interiorsCameraController.SetTilt(0.0f);
                    m_pSubStateMachine->StartStateMachine(0);
                }
                
                void InteriorExplorerState::Update(float dt)
                {
                    if(m_pSubStateMachine->GetCurrentStateIndex() >= 0)
                    {
                        m_pSubStateMachine->Update(dt);
                    }
                }
                
                void InteriorExplorerState::Exit(int nextState)
                {
                    if(m_pSubStateMachine->GetCurrentStateIndex() >= 0)
                    {
                        m_pSubStateMachine->StopStateMachine();
                    }
                    
                    m_interiorExplorerUserInteractionModel.SetEnabled(true);
                }
                
                void InteriorExplorerState::SetSubState(InteriorExplorerSubStates::Values stateIndex)
                {
                    
                    m_pSubStateMachine->ChangeToState(stateIndex);
                }
                
                void InteriorExplorerState::ReturnToWorldMode()
                {
                    m_appModeModel.SetAppMode(AppModes::SdkModel::WorldMode);
                }
                
                void InteriorExplorerState::ShowFailMessage()
                {
                    m_nativeUIFactories.AlertBoxFactory().CreateSingleOptionAlertBox("Error", "We couldn't find the data for this interior", m_failAlertHandler);
                }
                
                void InteriorExplorerState::OnFailAlertBoxDismissed()
                {
                }
                
                void InteriorExplorerState::SetLastEntryAttemptSuccessful(bool successful)
                {
                    m_interiorsExplorerModel.SetLastEntryAttemptSuccessful(successful);
                }
                
                bool InteriorExplorerState::GetLastEntryAttemptSuccessful() const
                {
                    return m_interiorsExplorerModel.GetLastEntryAttemptSuccessful();
                }
            }
        }
    }
}
