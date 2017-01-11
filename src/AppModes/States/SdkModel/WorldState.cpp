// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldState.h"
#include "IAppCameraController.h"
#include "TourService.h"
#include "IAppModeModel.h"
#include "InteriorSelectionModel.h"
#include "CameraHelpers.h"
#include "IAppCameraController.h"
#include "CameraState.h"
#include "RenderCamera.h"
#include "InteriorsCameraController.h"
#include "IUserIdleService.h"

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
                                       Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume)
                : m_cameraController(cameraController)
                , m_worldCameraHandle(worldCameraHandle)
                , m_cameraFrustumStreamingVolume(cameraFrustumStreamingVolume)
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
                    if(!m_cameraController.IsTransitionInFlight() && m_cameraFrustumStreamingVolume.GetForceMaximumRefinement())
                    {
                        m_cameraFrustumStreamingVolume.SetForceMaximumRefinement(false);
                    }
                }
            }
        }
    }
}
