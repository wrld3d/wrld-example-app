// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppModeStatesFactory.h"
#include "IAppCameraController.h"
#include "WorldState.h"
#include "InteriorExplorerState.h"
#include "TourState.h"
#include "AppGlobeCameraWrapper.h"
#include "AppInteriorCameraWrapper.h"
#include "IToursCameraController.h"
#include "AttractState.h"
#include "IUserIdleService.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                AppModeStatesFactory::AppModeStatesFactory(AppCamera::SdkModel::IAppCameraController& appCameraController,
                                                           AppCamera::SdkModel::AppGlobeCameraWrapper& worldCameraController,
                                                           AppCamera::SdkModel::AppInteriorCameraWrapper& interiorCameraController,
                                                           Tours::SdkModel::Camera::IToursCameraController& toursCameraController,
                                                           Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                                           InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdate,
                                                           InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                                           InteriorsExplorer::SdkModel::InteriorExplorerUserInteractionModel& interiorExplorerUserInteractionModel,
                                                           AppModes::SdkModel::IAppModeModel& appModeModel,
                                                           Tours::SdkModel::ITourService& tourService,
                                                           Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                           Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                           Eegeo::UI::NativeUIFactories& nativeUIFactories,
                                                           MyPinCreation::SdkModel::IMyPinCreationModel& myPinCreationModel,
                                                           VisualMap::SdkModel::IVisualMapService& visualMapService,
                                                           Eegeo::Input::IUserIdleService& userIdleService,
                                                           Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                                                           const bool attractModeEnabled,
                                                           const long long attractModeTimeout,
                                                           const std::vector<Eegeo::Space::LatLongAltitude>& cameraPositionSplinePoints,
                                                           const std::vector<Eegeo::Space::LatLongAltitude>& cameraTargetSplinePoints,
                                                           const Eegeo::Rendering::ScreenProperties& screenProperties)
                : m_appCameraController(appCameraController)
                , m_worldCameraController(worldCameraController)
                , m_interiorCameraController(interiorCameraController)
                , m_toursCameraController(toursCameraController)
                , m_cameraFrustumStreamingVolume(cameraFrustumStreamingVolume)
                , m_interiorVisibilityUpdate(interiorVisibilityUpdate)
                , m_interiorsExplorerModel(interiorsExplorerModel)
                , m_interiorExplorerUserInteractionModel(interiorExplorerUserInteractionModel)
                , m_appModeModel(appModeModel)
                , m_tourService(tourService)
                , m_interiorSelectionModel(interiorSelectionModel)
                , m_interiorInteractionModel(interiorInteractionModel)
                , m_nativeUIFactories(nativeUIFactories)
                , m_myPinCreationModel(myPinCreationModel)
                , m_visualMapService(visualMapService)
                , m_userIdleService(userIdleService)
                , m_resourceCeilingProvider(resourceCeilingProvider)
                , m_attractModeEnabled(attractModeEnabled)
                , m_attractModeTimeoutMs(attractModeTimeout)
                , m_cameraPositionSplinePoints(cameraPositionSplinePoints)
                , m_cameraTargetSplinePoints(cameraTargetSplinePoints)
                , m_screenProperties(screenProperties)
                {
                    
                }
                
                const std::vector<Helpers::IStateMachineState*> AppModeStatesFactory::CreateStateMachineStates()
                {
                    std::vector<Helpers::IStateMachineState*> states;
                    
                    const int worldCameraHandle = m_appCameraController.CreateCameraHandleFromController(m_worldCameraController);
                    const int interiorCameraHandle = m_appCameraController.CreateCameraHandleFromController(m_interiorCameraController);
                    const int toursCameraHandle = m_appCameraController.CreateCameraHandleFromController(m_toursCameraController);
                    
                    states.push_back(Eegeo_NEW(States::SdkModel::WorldState)(m_appCameraController,
                                                                             worldCameraHandle,
                                                                             m_tourService,
                                                                             m_interiorSelectionModel,
                                                                             m_appModeModel,
                                                                             m_interiorCameraController.GetInteriorCameraController(),
                                                                             m_userIdleService,
                                                                             m_attractModeEnabled,
                                                                             m_attractModeTimeoutMs));
                    
                    states.push_back(Eegeo_NEW(States::SdkModel::InteriorExplorerState)(m_appCameraController,
                                                                                        m_interiorSelectionModel,
                                                                                        m_interiorInteractionModel,
                                                                                        interiorCameraHandle,
                                                                                        m_tourService,
                                                                                        m_cameraFrustumStreamingVolume,
                                                                                        m_interiorVisibilityUpdate,
                                                                                        m_interiorsExplorerModel,
                                                                                        m_interiorExplorerUserInteractionModel,
                                                                                        m_appModeModel,
                                                                                        m_worldCameraController.GetGlobeCameraController(),
                                                                                        m_interiorCameraController.GetInteriorCameraController(),
                                                                                        m_nativeUIFactories,
                                                                                        m_myPinCreationModel));
                    
                    states.push_back(Eegeo_NEW(States::SdkModel::TourState)(m_appCameraController,
                                                                            toursCameraHandle,
                                                                            m_tourService,
                                                                            m_interiorSelectionModel,
                                                                            m_appModeModel,
                                                                            m_worldCameraController.GetGlobeCameraController(),
                                                                            m_interiorCameraController.GetInteriorCameraController(),
                                                                            m_interiorsExplorerModel,
                                                                            m_myPinCreationModel,
                                                                            m_visualMapService));

                    if (m_attractModeEnabled)
                    {
                        states.push_back(Eegeo_NEW(States::SdkModel::AttractState)(m_appModeModel,
                                                                                   m_appCameraController,
                                                                                   m_interiorCameraController.GetInteriorCameraController(),
                                                                                   m_interiorSelectionModel,
                                                                                   m_worldCameraController.GetTouchController(),
                                                                                   m_userIdleService,
                                                                                   m_resourceCeilingProvider,
                                                                                   m_attractModeTimeoutMs,
                                                                                   m_cameraPositionSplinePoints,
                                                                                   m_cameraTargetSplinePoints,
                                                                                   m_screenProperties));
                    }

                    return states;
                }
            }
        }
    }
}
