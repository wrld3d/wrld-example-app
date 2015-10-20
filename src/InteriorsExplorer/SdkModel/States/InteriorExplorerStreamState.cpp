// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorExplorerStreamState.h"
#include "IAppCameraController.h"
#include "InteriorController.h"
#include "CameraFrustumStreamingVolume.h"
#include "InteriorVisibilityUpdater.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace States
            {
                InteriorExplorerStreamState::InteriorExplorerStreamState(AppModes::States::SdkModel::InteriorExplorerState& parentState,
                                                                         Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                                         Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                                                         InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater)
                : m_parentState(parentState)
                , m_interiorController(interiorController)
                , m_cameraFrustumStreamingVolume(cameraFrustumStreamingVolume)
                , m_interiorVisibilityUpdater(interiorVisibilityUpdater)
                , m_maxTimeout(5.0f)
                {
                }
                
                InteriorExplorerStreamState::~InteriorExplorerStreamState()
                {
                }
                
                void InteriorExplorerStreamState::Enter()
                {
                    m_cameraFrustumStreamingVolume.SetForceMaximumRefinement(true);
                    
                    m_timeUntilTimeout = m_maxTimeout;
                }
                
                void InteriorExplorerStreamState::Update(float dt)
                {
                    m_timeUntilTimeout -= dt;
                    if(m_timeUntilTimeout <=0.0f)
                    {
                        m_parentState.ShowFailMessage();
                        m_parentState.SetSubState(AppModes::States::SdkModel::InteriorExplorerSubStates::Exit);
                        return;
                    }
                    
                    if(m_interiorController.InteriorInScene())
                    {
                        m_interiorVisibilityUpdater.SetInteriorShouldDisplay(true);
                        m_parentState.SetSubState(AppModes::States::SdkModel::InteriorExplorerSubStates::View);
                    }
                }
                
                void InteriorExplorerStreamState::Exit()
                {
                    m_cameraFrustumStreamingVolume.SetForceMaximumRefinement(false);
                }
                
            }
            
        }
    }
}