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
                                       int worldCameraHandle)
                : m_cameraController(cameraController)
                , m_worldCameraHandle(worldCameraHandle)
                {
                }
                
                WorldState::~WorldState()
                {
                }
                
                void WorldState::Enter(int previousState)
                {
                    m_cameraController.TransitionToCameraWithHandle(m_worldCameraHandle);
                }
                
                void WorldState::Update(float dt)
                {
                }
                
                void WorldState::Exit(int nextState)
                {
                }
            }
        }
    }
}
