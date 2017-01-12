// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "AttractState.h"
#include "AttractModeEnteringState.h"
#include "IAppCameraController.h"
#include "StateMachine.h"

namespace ExampleApp
{
    namespace AttractMode
    {
        namespace SdkModel
        {
            namespace States
            {
                namespace
                {
                    const double JumpDistanceThreshold = 25000.0;
                    const float TransitionDuration = 6.0f;
                }

                AttractModeEnteringState::AttractModeEnteringState(Helpers::StateMachine& stateMachine,
                                                                   AppCamera::SdkModel::IAppCameraController& cameraController,
                                                                   const int attractModeCameraHandle)
                : m_stateMachine(stateMachine)
                , m_cameraController(cameraController)
                , m_attractModeCameraHandle(attractModeCameraHandle)
                {
                }
                
                void AttractModeEnteringState::Enter(int previousState)
                {
                    m_cameraController.TransitionToCameraWithHandle(m_attractModeCameraHandle, JumpDistanceThreshold, TransitionDuration);
                }
                
                void AttractModeEnteringState::Update(float dt)
                {
                    if(!m_cameraController.IsTransitionInFlight())
                    {
                        m_stateMachine.ChangeToState(AppModes::States::SdkModel::AttractModeSubStates::View);
                    }
                }
                
                void AttractModeEnteringState::Exit(int nextState)
                {
                }
            }
        }
    }
}
