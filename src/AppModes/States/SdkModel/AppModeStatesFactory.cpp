// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppModeStatesFactory.h"
#include "IAppCameraController.h"
#include "WorldState.h"
#include "InteriorExplorerState.h"
#include "AppGlobeCameraWrapper.h"
#include "AppInteriorCameraWrapper.h"
#include "AttractState.h"
#include "IUserIdleService.h"
#include "LatLongAltitude.h"
#include "ScreenProperties.h"
#include "BidirectionalBus.h"
#include "IFlattenButtonModel.h"
#include "NavigationService.h"
#include "CameraTransitionService.h"
#include "ILocationService.h"
#include "Search.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                AppModeStatesFactory::AppModeStatesFactory(AppCamera::SdkModel::IAppCameraController& appCameraController,
                                                           Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController& cameraSplinePlaybackController,
                                                           AppCamera::SdkModel::AppGlobeCameraWrapper& worldCameraController,
                                                           AppCamera::SdkModel::AppInteriorCameraWrapper& interiorCameraController,
                                                           Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                                           InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdate,
                                                           InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                                           InteriorsExplorer::SdkModel::InteriorExplorerUserInteractionModel& interiorExplorerUserInteractionModel,
                                                           AppModes::SdkModel::IAppModeModel& appModeModel,
                                                           Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                           Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                           Eegeo::UI::NativeUIFactories& nativeUIFactories,
                                                           VisualMap::SdkModel::IVisualMapService& visualMapService,
                                                           Eegeo::Location::ILocationService& locationService,
                                                           Eegeo::Input::IUserIdleService& userIdleService,
                                                           const bool attractModeEnabled,
                                                           const std::vector<Eegeo::Space::LatLongAltitude>& cameraPositionSplinePoints,
                                                           const std::vector<Eegeo::Space::LatLongAltitude>& cameraTargetSplinePoints,
                                                           const float attractModePlaybackSpeed,
                                                           const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                           ExampleAppMessaging::TMessageBus& messageBus,
                                                           Eegeo::Location::NavigationService& navigationService,
                                                           Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                           FlattenButton::SdkModel::IFlattenButtonModel& flattenButtonModel)
                : m_appCameraController(appCameraController)
                , m_cameraSplinePlaybackController(cameraSplinePlaybackController)
                , m_worldCameraController(worldCameraController)
                , m_interiorCameraController(interiorCameraController)
                , m_cameraFrustumStreamingVolume(cameraFrustumStreamingVolume)
                , m_interiorVisibilityUpdate(interiorVisibilityUpdate)
                , m_interiorsExplorerModel(interiorsExplorerModel)
                , m_interiorExplorerUserInteractionModel(interiorExplorerUserInteractionModel)
                , m_appModeModel(appModeModel)
                , m_interiorSelectionModel(interiorSelectionModel)
                , m_interiorInteractionModel(interiorInteractionModel)
                , m_nativeUIFactories(nativeUIFactories)
                , m_visualMapService(visualMapService)
                , m_locationService(locationService)
                , m_userIdleService(userIdleService)
                , m_attractModeEnabled(attractModeEnabled)
                , m_cameraPositionSplinePoints(cameraPositionSplinePoints)
                , m_cameraTargetSplinePoints(cameraTargetSplinePoints)
                , m_attractModePlaybackSpeed(attractModePlaybackSpeed)
                , m_screenProperties(screenProperties)
                , m_messageBus(messageBus)
                , m_navigationService(navigationService)
                , m_searchQueryPerformer(searchQueryPerformer)
                , m_flattenButtonModel(flattenButtonModel)
                {
                    
                }
                
                const std::vector<Helpers::IStateMachineState*> AppModeStatesFactory::CreateStateMachineStates(GlobalAppModeTransitionRules& globalAppModeTransitionRules)
                {
                    std::vector<Helpers::IStateMachineState*> states;
                    
                    const int worldCameraHandle = globalAppModeTransitionRules.GetWorldCameraHandle();
                    const int interiorCameraHandle = globalAppModeTransitionRules.GetInteriorsCameraHandle();
                    
                    states.push_back(Eegeo_NEW(States::SdkModel::WorldState)(m_appCameraController,
                                                                             worldCameraHandle,
                                                                             m_cameraFrustumStreamingVolume,
                                                                             m_visualMapService,
                                                                             m_interiorsExplorerModel));
                    
                    states.push_back(Eegeo_NEW(States::SdkModel::InteriorExplorerState)(m_appCameraController,
                                                                                        m_interiorSelectionModel,
                                                                                        m_interiorInteractionModel,
                                                                                        interiorCameraHandle,
                                                                                        m_cameraFrustumStreamingVolume,
                                                                                        m_interiorVisibilityUpdate,
                                                                                        m_interiorsExplorerModel,
                                                                                        m_interiorExplorerUserInteractionModel,
                                                                                        m_appModeModel,
                                                                                        m_interiorCameraController.GetInteriorCameraController(),
                                                                                        m_nativeUIFactories));

                    if (m_attractModeEnabled)
                    {
                        states.push_back(Eegeo_NEW(States::SdkModel::AttractState)(m_appModeModel,
                                                                                   m_appCameraController,
                                                                                   m_cameraSplinePlaybackController,
                                                                                   m_worldCameraController,
                                                                                   worldCameraHandle,
                                                                                   m_interiorCameraController.GetInteriorCameraController(),
                                                                                   m_worldCameraController.GetTouchController(),
                                                                                   m_locationService,
                                                                                   m_userIdleService,
                                                                                   m_cameraPositionSplinePoints,
                                                                                   m_cameraTargetSplinePoints,
                                                                                   m_attractModePlaybackSpeed,
                                                                                   m_screenProperties,
                                                                                   m_messageBus,
                                                                                   m_navigationService,
                                                                                   m_searchQueryPerformer,
                                                                                   m_visualMapService,
                                                                                   m_flattenButtonModel));
                    }

                    return states;
                }
            }
        }
    }
}
