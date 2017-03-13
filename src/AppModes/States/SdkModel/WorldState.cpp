// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldState.h"
#include "IAppCameraController.h"
#include "IAppModeModel.h"
#include "InteriorSelectionModel.h"
#include "CameraHelpers.h"
#include "IAppCameraController.h"
#include "CameraState.h"
#include "RenderCamera.h"
#include "InteriorsCameraController.h"
#include "IUserIdleService.h"
#include "IVisualMapService.h"
#include "InteriorsExplorerModel.h"

#include <limits>

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                WorldState::WorldState(AppCamera::SdkModel::IAppCameraController& cameraController,
                                       int worldCameraHandle,
                                       Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                       VisualMap::SdkModel::IVisualMapService& visualMapService,
                                       InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel)
                : m_cameraController(cameraController)
                , m_worldCameraHandle(worldCameraHandle)
                , m_cameraFrustumStreamingVolume(cameraFrustumStreamingVolume)
                , m_visualMapService(visualMapService)
                , m_interiorsExplorerModel(interiorsExplorerModel)
                , m_previousStateWasInterior(false)
                , m_transitionInFlightCallback(this, &WorldState::OnTransitionInFlight)
                {
                }
                
                WorldState::~WorldState()
                {
                }
                
                void WorldState::Enter(int previousState)
                {
                    m_cameraController.TransitionToCameraWithHandle(m_worldCameraHandle);
                    m_cameraController.InsertTransitioInFlightChangedCallback(m_transitionInFlightCallback);
                    if(previousState == AppModes::SdkModel::InteriorMode && m_interiorsExplorerModel.GetLastEntryAttemptSuccessful())
                    {
                        m_previousStateWasInterior = true;
                    }
                }
                
                void WorldState::Update(float dt)
                {
                }
                
                void WorldState::Exit(int nextState)
                {
                    m_cameraController.RemoveTransitioInFlightChangedCallback(m_transitionInFlightCallback);
                }
                
                void WorldState::OnTransitionInFlight()
                {
                    if(!m_cameraController.IsTransitionInFlight())
                    {
                        if(m_cameraFrustumStreamingVolume.GetForceMaximumRefinement())
                        {
                            m_cameraFrustumStreamingVolume.SetForceMaximumRefinement(false);
                        }
                        
                        if(m_previousStateWasInterior)
                        {
                            m_previousStateWasInterior = false;
                            m_visualMapService.RestorePreviousMapState();
                        }
                    }
                }
            }
        }
    }
}
