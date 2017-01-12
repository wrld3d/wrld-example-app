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
                AttractModeViewingState::AttractModeViewingState(AppModes::States::SdkModel::AttractState& attractState,
                                                                 Eegeo::Input::IUserIdleService& userIdleService,
                                                                 Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController& cameraSplinePlaybackController)
                : m_attractState(attractState)
                , m_idleTimeAtStartMs(0)
                , m_userIdleService(userIdleService)
                , m_cameraSplinePlaybackController(cameraSplinePlaybackController)
                {
                }
                
                void AttractModeViewingState::Enter(int previousState)
                {
                    m_idleTimeAtStartMs = m_userIdleService.GetUserIdleTimeMs();
                    m_cameraSplinePlaybackController.Play();
                }
                
                void AttractModeViewingState::Update(float dt)
                {
                    if (m_userIdleService.GetUserIdleTimeMs() < m_idleTimeAtStartMs)
                    {
                        m_attractState.NotifySubStateComplete();
                    }
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
