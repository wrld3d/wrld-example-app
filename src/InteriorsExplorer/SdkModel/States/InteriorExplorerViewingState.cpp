// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorExplorerViewingState.h"
#include "IAppCameraController.h"
#include "InteriorController.h"
#include "CameraFrustumStreamingVolume.h"
#include "InteriorVisibilityUpdater.h"
#include "InteriorsExplorerModel.h"

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
                                                                           Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume)
                : m_parentState(parentState)
                , m_interiorExplorerModel(interiorExplorerModel)
                , m_cameraFrustumStreamingVolume(cameraFrustumStreamingVolume)
                , m_exitCallback(this, &InteriorExplorerViewingState::OnInteriorExplorerExit)
                , m_exiting(false)
                {
                }
                
                InteriorExplorerViewingState::~InteriorExplorerViewingState()
                {
                }
                
                void InteriorExplorerViewingState::Enter()
                {
                    m_cameraFrustumStreamingVolume.SetForceMaximumRefinement(true);
                    m_interiorExplorerModel.ShowInteriorExplorer();
                    m_interiorExplorerModel.InsertInteriorExplorerExitedCallback(m_exitCallback);
                    m_exiting = false;
                }
                
                void InteriorExplorerViewingState::Update(float dt)
                {
                    if(m_exiting)
                    {
                        m_parentState.SetSubState(AppModes::States::SdkModel::InteriorExplorerSubStates::Exit);
                    }
                }
                
                void InteriorExplorerViewingState::Exit()
                {
                    m_cameraFrustumStreamingVolume.SetForceMaximumRefinement(false);
                    m_interiorExplorerModel.RemoveInteriorExplorerExitedCallback(m_exitCallback);
                    m_interiorExplorerModel.HideInteriorExplorer();
                }
                
                void InteriorExplorerViewingState::OnInteriorExplorerExit()
                {
                    m_exiting = true;
                }
                
            }
            
        }
    }
}