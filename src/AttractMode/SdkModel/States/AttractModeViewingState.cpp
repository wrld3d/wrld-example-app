// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "AttractModeViewingState.h"
#include "CameraSplinePlaybackController.h"
#include "IAppModeModel.h"
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
                AttractModeViewingState::AttractModeViewingState(AppModes::SdkModel::IAppModeModel& appModeModel,
                                                                 Eegeo::Input::IUserIdleService& userIdleService,
                                                                 Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController& cameraSplinePlaybackController)
                : m_idleTimeAtStartMs(0)
                , m_appModeModel(appModeModel)
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
                        m_appModeModel.SetAppMode(AppModes::SdkModel::WorldMode);
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
