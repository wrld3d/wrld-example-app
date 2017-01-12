// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "AttractState.h"
#include "AttractModeViewingState.h"
#include "CameraSplinePlaybackController.h"
#include "IUserIdleService.h"
#include "StateMachine.h"
#include "TimeHelpers.h"

namespace ExampleApp
{
    namespace AttractMode
    {
        namespace SdkModel
        {
            namespace States
            {
                AttractModeViewingState::AttractModeViewingState(Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController& cameraSplinePlaybackController)
                : m_cameraSplinePlaybackController(cameraSplinePlaybackController)
                {
                }
                
                void AttractModeViewingState::Enter(int previousState)
                {
                    m_cameraSplinePlaybackController.Play();
                }
                
                void AttractModeViewingState::Update(float dt)
                {
                    m_cameraSplinePlaybackController.Update(dt);
                }
                
                void AttractModeViewingState::Exit(int nextState)
                {
                    m_cameraSplinePlaybackController.Stop();
                }
            }
        }
    }
}
