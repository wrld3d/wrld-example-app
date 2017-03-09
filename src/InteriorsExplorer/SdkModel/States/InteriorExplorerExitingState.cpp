// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorExplorerExitingState.h"
#include "IAppCameraController.h"
#include "CameraFrustumStreamingVolume.h"
#include "InteriorVisibilityUpdater.h"
#include "InteriorsExplorerModel.h"
#include "InteriorSelectionModel.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace States
            {
                InteriorExplorerExitingState::InteriorExplorerExitingState(AppModes::States::SdkModel::InteriorExplorerState& parentState,
                                                                           Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                           Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                                                           InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                                                           InteriorsExplorerModel& interiorsExplorerModel)
                : m_parentState(parentState)
                , m_interiorSelectionModel(interiorSelectionModel)
                , m_cameraFrustumStreamingVolume(cameraFrustumStreamingVolume)
                , m_interiorVisibilityUpdater(interiorVisibilityUpdater)
                , m_interiorsExplorerModel(interiorsExplorerModel)
                {
                }
                
                InteriorExplorerExitingState::~InteriorExplorerExitingState()
                {
                }
                
                void InteriorExplorerExitingState::Enter(int previousState)
                {
                    
                    m_interiorVisibilityUpdater.SetInteriorShouldDisplay(false);
                    m_interiorSelectionModel.ClearSelection();
                }
                
                void InteriorExplorerExitingState::Update(float dt)
                {
                    if (!m_interiorSelectionModel.IsInteriorSelected())
                    {
                        m_parentState.ReturnToWorldMode();
                        
                    }
                }
                
                void InteriorExplorerExitingState::Exit(int nextState)
                {
                    
                }
            }
            
        }
    }
}
