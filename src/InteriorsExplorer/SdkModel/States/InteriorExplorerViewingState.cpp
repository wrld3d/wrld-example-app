// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorExplorerViewingState.h"
#include "IAppCameraController.h"
#include "CameraFrustumStreamingVolume.h"
#include "InteriorVisibilityUpdater.h"
#include "InteriorsExplorerModel.h"
#include "InteriorExplorerUserInteractionModel.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace States
            {
                InteriorExplorerViewingState::InteriorExplorerViewingState(AppModes::States::SdkModel::InteriorExplorerState& parentState,
                                                                           InteriorsExplorerModel& interiorExplorerModel,
                                                                           InteriorExplorerUserInteractionModel& interiorExplorerUserInteractionModel)
                : m_parentState(parentState)
                , m_interiorExplorerModel(interiorExplorerModel)
                , m_interiorExplorerUserInteractionModel(interiorExplorerUserInteractionModel)
                , m_exitCallback(this, &InteriorExplorerViewingState::OnInteriorExplorerExit)
                , m_exiting(false)
                {
                }
                
                InteriorExplorerViewingState::~InteriorExplorerViewingState()
                {
                }
                
                void InteriorExplorerViewingState::Enter(int previousState)
                {
                    m_interiorExplorerModel.ShowInteriorExplorer();
                    m_interiorExplorerModel.InsertInteriorExplorerExitedCallback(m_exitCallback);
                    m_exiting = false;
                    m_interiorExplorerUserInteractionModel.SetEnabled(true);
                }
                
                void InteriorExplorerViewingState::Update(float dt)
                {
                    if(m_exiting)
                    {
                        m_parentState.SetSubState(AppModes::States::SdkModel::InteriorExplorerSubStates::Exit);
                    }
                }
                
                void InteriorExplorerViewingState::Exit(int nextState)
                {
                    m_interiorExplorerModel.RemoveInteriorExplorerExitedCallback(m_exitCallback);
                    m_interiorExplorerModel.HideInteriorExplorer();
                }
                
                void InteriorExplorerViewingState::OnInteriorExplorerExit()
                {
                    m_exiting = true;
                    m_interiorExplorerUserInteractionModel.SetEnabled(false);
                }
                
            }
            
        }
    }
}