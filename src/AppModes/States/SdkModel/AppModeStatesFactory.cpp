// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppModeStatesFactory.h"
#include "IAppCameraController.h"
#include "WorldState.h"
#include "InteriorExplorerState.h"
#include "TourState.h"
#include "AppGlobeCameraWrapper.h"
#include "AppInteriorCameraWrapper.h"
#include "IToursCameraController.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                AppModeStatesFactory::AppModeStatesFactory(const std::shared_ptr<AppCamera::SdkModel::IAppCameraController>& appCameraController,
                                                           const std::shared_ptr<AppCamera::SdkModel::AppGlobeCameraWrapper>& worldCameraController,
                                                           const std::shared_ptr<AppCamera::SdkModel::AppInteriorCameraWrapper>& interiorCameraController,
                                                           const std::shared_ptr<Tours::SdkModel::Camera::IToursCameraController>& toursCameraController,
                                                           const std::shared_ptr<Eegeo::Streaming::CameraFrustumStreamingVolume>& cameraFrustumStreamingVolume,
                                                           const std::shared_ptr<InteriorsExplorer::SdkModel::InteriorVisibilityUpdater>& interiorVisibilityUpdater,
                                                           const std::shared_ptr<InteriorsExplorer::SdkModel::InteriorsExplorerModel>& interiorsExplorerModel,
                                                           const std::shared_ptr<InteriorsExplorer::SdkModel::InteriorExplorerUserInteractionModel>& interiorExplorerUserInteractionModel,
                                                           const std::shared_ptr<AppModes::SdkModel::IAppModeModel>& appModeModel,
                                                           const std::shared_ptr<Tours::SdkModel::ITourService>& tourService,
                                                           const std::shared_ptr<Eegeo::Resources::Interiors::InteriorSelectionModel>& interiorSelectionModel,
                                                           const std::shared_ptr<Eegeo::Resources::Interiors::InteriorInteractionModel>& interiorInteractionModel,
                                                           const std::shared_ptr<Eegeo::UI::NativeUIFactories>& nativeUIFactories,
                                                           const std::shared_ptr<MyPinCreation::SdkModel::IMyPinCreationModel>& myPinCreationModel,
                                                           const std::shared_ptr<VisualMap::SdkModel::IVisualMapService>& visualMapService)
                : m_appCameraController(appCameraController)
                , m_worldCameraController(worldCameraController)
                , m_interiorCameraController(interiorCameraController)
                , m_toursCameraController(toursCameraController)
                , m_cameraFrustumStreamingVolume(cameraFrustumStreamingVolume)
                , m_interiorVisibilityUpdate(interiorVisibilityUpdater)
                , m_interiorsExplorerModel(interiorsExplorerModel)
                , m_interiorExplorerUserInteractionModel(interiorExplorerUserInteractionModel)
                , m_appModeModel(appModeModel)
                , m_tourService(tourService)
                , m_interiorSelectionModel(interiorSelectionModel)
                , m_interiorInteractionModel(interiorInteractionModel)
                , m_nativeUIFactories(nativeUIFactories)
                , m_myPinCreationModel(myPinCreationModel)
                , m_visualMapService(visualMapService)
                {
                    
                }
                
                const std::vector<Helpers::IStateMachineState*> AppModeStatesFactory::CreateStateMachineStates()
                {
                    std::vector<Helpers::IStateMachineState*> states;
                    
                    const int worldCameraHandle = m_appCameraController->CreateCameraHandleFromController(*m_worldCameraController);
                    const int interiorCameraHandle = m_appCameraController->CreateCameraHandleFromController(*m_interiorCameraController);
                    const int toursCameraHandle = m_appCameraController->CreateCameraHandleFromController(*m_toursCameraController);
                    
                    states.push_back(Eegeo_NEW(States::SdkModel::WorldState)(*m_appCameraController,
                                                                             worldCameraHandle,
                                                                             *m_tourService,
                                                                             *m_interiorSelectionModel,
                                                                             *m_appModeModel,
                                                                             m_interiorCameraController->GetInteriorCameraController()));
                    
                    states.push_back(Eegeo_NEW(States::SdkModel::InteriorExplorerState)(*m_appCameraController,
                                                                                        *m_interiorSelectionModel,
                                                                                        *m_interiorInteractionModel,
                                                                                        interiorCameraHandle,
                                                                                        *m_tourService,
                                                                                        *m_cameraFrustumStreamingVolume,
                                                                                        *m_interiorVisibilityUpdate,
                                                                                        *m_interiorsExplorerModel,
                                                                                        *m_interiorExplorerUserInteractionModel,
                                                                                        *m_appModeModel,
                                                                                        m_worldCameraController->GetGlobeCameraController(),
                                                                                        m_interiorCameraController->GetInteriorCameraController(),
                                                                                        *m_nativeUIFactories,
                                                                                        *m_myPinCreationModel));
                    
                    states.push_back(Eegeo_NEW(States::SdkModel::TourState)(*m_appCameraController,
                                                                            toursCameraHandle,
                                                                            *m_tourService,
                                                                            *m_interiorSelectionModel,
                                                                            *m_appModeModel,
                                                                            m_worldCameraController->GetGlobeCameraController(),
                                                                            m_interiorCameraController->GetInteriorCameraController(),
                                                                            *m_interiorsExplorerModel,
                                                                            *m_myPinCreationModel,
                                                                            *m_visualMapService));

                    return states;
                }
            }
        }
    }
}