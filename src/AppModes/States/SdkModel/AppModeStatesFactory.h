// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IAppModeStatesFactory.h"
#include "IStateMachineState.h"
#include "Interiors.h"
#include "Streaming.h"
#include "InteriorsExplorer.h"
#include "AppCamera.h"
#include "AppModes.h"
#include "EegeoUI.h"
#include "MyPinCreation.h"
#include "IUserIdleService.h"
#include "LatLongAltitude.h"
#include "ScreenProperties.h"
#include "GlobalAppModeTransitionRules.h"
#include "BidirectionalBus.h"
#include "FlattenButton.h"
#include "NavigationService.h"
#include "CameraTransitions.h"
#include "ILocationService.h"
#include "Search.h"

#include "VisualMap.h"
#include "IFlattenButtonModel.h"
#include <vector>

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                class AppModeStatesFactory : public AppModes::SdkModel::IAppModeStatesFactory
                {
                private:
                    AppCamera::SdkModel::IAppCameraController& m_appCameraController;
                    Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController& m_cameraSplinePlaybackController;
                    AppCamera::SdkModel::AppGlobeCameraWrapper& m_worldCameraController;
                    AppCamera::SdkModel::AppInteriorCameraWrapper& m_interiorCameraController;
                    Eegeo::Streaming::CameraFrustumStreamingVolume& m_cameraFrustumStreamingVolume;
                    InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& m_interiorVisibilityUpdate;
                    AppModes::SdkModel::IAppModeModel& m_appModeModel;
                    InteriorsExplorer::SdkModel::InteriorsExplorerModel& m_interiorsExplorerModel;
                    InteriorsExplorer::SdkModel::InteriorExplorerUserInteractionModel& m_interiorExplorerUserInteractionModel;
                    Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                    Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                    Eegeo::UI::NativeUIFactories& m_nativeUIFactories;
                    VisualMap::SdkModel::IVisualMapService& m_visualMapService;
                    FlattenButton::SdkModel::IFlattenButtonModel& m_flattenButtonModel;

                    Eegeo::Location::ILocationService& m_locationService;
                    Eegeo::Input::IUserIdleService& m_userIdleService;
                    const bool m_attractModeEnabled;
                    const std::vector<Eegeo::Space::LatLongAltitude>& m_cameraPositionSplinePoints;
                    const std::vector<Eegeo::Space::LatLongAltitude>& m_cameraTargetSplinePoints;
                    const float m_attractModePlaybackSpeed;
                    const Eegeo::Rendering::ScreenProperties& m_screenProperties;

                    ExampleAppMessaging::TMessageBus& m_messageBus;

                    Eegeo::Location::NavigationService& m_navigationService;
                    Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;
                    
                public:
                    
                    AppModeStatesFactory(AppCamera::SdkModel::IAppCameraController& appCameraController,
                                         Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController& cameraSplinePlaybackController,
                                         AppCamera::SdkModel::AppGlobeCameraWrapper& worldCameraController,
                                         AppCamera::SdkModel::AppInteriorCameraWrapper& interiorCameraController,
                                         Eegeo::Streaming::CameraFrustumStreamingVolume& cameraFrustumStreamingVolume,
                                         InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
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
                                         FlattenButton::SdkModel::IFlattenButtonModel& flattenButtonModel);
                    
                    ~AppModeStatesFactory()
                    {
                        
                    }
                    
                    const std::vector<Helpers::IStateMachineState*> CreateStateMachineStates(GlobalAppModeTransitionRules& globalAppModeTransitionRules);
                };
            }
        }
    }
}
