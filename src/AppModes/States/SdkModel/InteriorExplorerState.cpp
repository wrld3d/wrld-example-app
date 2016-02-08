// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorExplorerState.h"
#include "IAppCameraController.h"
#include "InteriorController.h"
#include "InteriorExplorerSetupState.h"
#include "InteriorExplorerStreamState.h"
#include "InteriorExplorerViewingState.h"
#include "InteriorExplorerExitingState.h"
#include "InteriorSelectionModel.h"
#include "IAppModeModel.h"
#include "InteriorsExplorerCameraController.h"
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
#include "ITourService.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                InteriorExplorerState::InteriorExplorerState(AppCamera::SdkModel::IAppCameraController& cameraController,
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
                                                             MyPinCreation::SdkModel::IMyPinCreationModel& myPinCreationModel)
                : m_tourService(tourService)
                , m_tourStartedCallback(this, &InteriorExplorerState::OnTourStarted)
                , m_interiorExplorerUserInteractionModel(interiorExplorerUserInteractionModel)
                , m_appModeModel(appModeModel)
                , m_worldCameraController(worldCameraController)
                , m_interiorsCameraController(interiorsCameraController)
                , m_nativeUIFactories(nativeUIFactories)
                , m_failAlertHandler(this, &InteriorExplorerState::OnFailAlertBoxDismissed)
                , m_myPinCreationModel(myPinCreationModel)
                , m_lastEntryAttemptSuccessful(false)
                {
                    
                    m_subStates.push_back(Eegeo_NEW(InteriorsExplorer::SdkModel::States::InteriorExplorerSetupState)(*this,
                                                                                                                     cameraController,
                                                                                                                     interiorCameraHandle));
                    
                    m_subStates.push_back(Eegeo_NEW(InteriorsExplorer::SdkModel::States::InteriorExplorerStreamState)(*this,
                                                                                                                      interiorController,
                                                                                                                      cameraFrustumStreamingVolume,
                                                                                                                      interiorVisibilityUpdater));
                    
                    m_subStates.push_back(Eegeo_NEW(InteriorsExplorer::SdkModel::States::InteriorExplorerViewingState)(*this,
                                                                                                                       interiorsExplorerModel,
                                                                                                                       interiorExplorerUserInteractionModel,
                                                                                                                       cameraFrustumStreamingVolume));
                    
                    m_subStates.push_back(Eegeo_NEW(InteriorsExplorer::SdkModel::States::InteriorExplorerExitingState)(*this,
                                                                                                                       interiorController,
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
                    m_tourService.RegisterTourStartedCallback(m_tourStartedCallback);
                    m_myPinCreationModel.SetCreationStage(MyPinCreation::Inactive);
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
                    Eegeo::Space::LatLongAltitude latLong = Eegeo::Space::LatLongAltitude::FromECEF(m_interiorsCameraController.GetCameraState().InterestPointEcef());
                    const float interestDistance = 500.0f;
                    m_worldCameraController.SetView(latLong.GetLatitudeInDegrees(), latLong.GetLongitudeInDegrees(),
                                                    m_interiorsCameraController.GetHeadingDegrees(),
                                                    interestDistance);
                    m_worldCameraController.GetGlobeCameraController().ApplyTilt(0.0f);
                    
                    if(m_pSubStateMachine->GetCurrentStateIndex() >= 0)
                    {
                        m_pSubStateMachine->StopStateMachine();
                    }
                    
                    m_tourService.UnregisterTourStartedCallback(m_tourStartedCallback);
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
                
                void InteriorExplorerState::OnTourStarted()
                {
                    m_appModeModel.SetAppMode(ExampleApp::AppModes::SdkModel::TourMode);
                }
                
                void InteriorExplorerState::SetLastEntryAttemptSuccessful(bool successful)
                {
                    m_lastEntryAttemptSuccessful = successful;
                }
                
                bool InteriorExplorerState::GetLastEntryAttemptSuccessful() const
                {
                    return m_lastEntryAttemptSuccessful;
                }
            }
        }
    }
}