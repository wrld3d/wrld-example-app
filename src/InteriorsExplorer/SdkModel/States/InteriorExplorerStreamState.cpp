// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorExplorerStreamState.h"
#include "IAppCameraController.h"
#include "IInteriorController.h"
#include "CameraFrustumStreamingVolume.h"
#include "InteriorVisibilityUpdater.h"
#include "InteriorInteractionModel.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace States
            {
                InteriorExplorerStreamState::InteriorExplorerStreamState(AppModes::States::SdkModel::InteriorExplorerState& parentState,
                                                                         const Eegeo::Resources::Interiors::IInteriorController& interiorController,
                                                                         const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                         Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                                                         InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater)
                : m_parentState(parentState)
                , m_interiorController(interiorController)
                , m_interiorInteractionModel(interiorInteractionModel)
                , m_cameraFrustumStreamingVolume(cameraFrustumStreamingVolume)
                , m_interiorVisibilityUpdater(interiorVisibilityUpdater)
                , m_maxTimeout(5.0f)
                {
                }
                
                InteriorExplorerStreamState::~InteriorExplorerStreamState()
                {
                }
                
                void InteriorExplorerStreamState::Enter(int previousState)
                {
                    m_cameraFrustumStreamingVolume.SetForceMaximumRefinement(true);
                    
                    m_timeUntilTimeout = m_maxTimeout;
                }
                
                void InteriorExplorerStreamState::Update(float dt)
                {
                    m_timeUntilTimeout -= dt;
                    if(m_timeUntilTimeout <= 0.0f)
                    {
                        m_parentState.SetLastEntryAttemptSuccessful(false);
                        m_parentState.ShowFailMessage();
                        m_parentState.SetSubState(AppModes::States::SdkModel::InteriorExplorerSubStates::Exit);
                        return;
                    }
                    
                    if (m_interiorInteractionModel.HasInteriorModel())
                    {
                        m_parentState.SetLastEntryAttemptSuccessful(true);
                        m_interiorVisibilityUpdater.SetInteriorShouldDisplay(true);
                        m_parentState.SetSubState(AppModes::States::SdkModel::InteriorExplorerSubStates::View);
                    }
                }
                
                void InteriorExplorerStreamState::Exit(int nextState)
                {
                    m_cameraFrustumStreamingVolume.SetForceMaximumRefinement(false);
                }
                
            }
            
        }
    }
}