// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorExplorerSetupState.h"
#include "IAppCameraController.h"
#include "InteriorController.h"
#include "InteriorsExplorerModel.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace States
            {
                InteriorExplorerSetupState::InteriorExplorerSetupState(AppModes::States::SdkModel::InteriorExplorerState& parentState,
                                                                       InteriorsExplorerModel& interiorsExplorerModel,
                                                                       AppCamera::SdkModel::IAppCameraController& cameraController,
                                                                       int interiorCameraHandle)
                : m_parentState(parentState)
                , m_interiorsExplorerModel(interiorsExplorerModel)
                , m_cameraController(cameraController)
                , m_interiorCameraHandle(interiorCameraHandle)
                {
                }
                
                InteriorExplorerSetupState::~InteriorExplorerSetupState()
                {
                }
                
                void InteriorExplorerSetupState::Enter(int previousState)
                {
                    m_interiorsExplorerModel.SaveCurrentMapState();
                    m_interiorsExplorerModel.ChangeToInteriorMapState();
                    m_cameraController.TransitionToCameraWithHandle(m_interiorCameraHandle);
                }
                
                void InteriorExplorerSetupState::Update(float dt)
                {
                    if(!m_cameraController.IsTransitionInFlight())
                    {
                        m_parentState.SetSubState(AppModes::States::SdkModel::InteriorExplorerSubStates::Stream);
                    }
                }
                
                void InteriorExplorerSetupState::Exit(int nextState)
                {
                    
                }
                
            }
        }
    }
}