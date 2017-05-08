// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "IStateMachineState.h"
#include "AppCamera.h"
#include "AppModes.h"
#include "IAppModeModel.h"
#include "ICallback.h"
#include "Interiors.h"
#include "InteriorsExplorer.h"
#include "AppCameraSplinePlaybackWrapper.h"
#include "IUserIdleService.h"
#include "CatmullRomSpline.h"
#include "BidirectionalBus.h"
#include "NavigationService.h"
#include "AttractModeEnteringState.h"
#include "AttractModeViewingState.h"
#include "AttractModeExitingState.h"
#include "CameraTransitionService.h"
#include "ILocationService.h"
#include "Search.h"
#include "VisualMap.h"
#include "AttractModeStates.h"
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
                class AttractState : public Helpers::IStateMachineState
                {
                private:
                    AppModes::SdkModel::IAppModeModel& m_appModeModel;
                    AppCamera::SdkModel::IAppCameraController& m_cameraController;
                    Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController& m_cameraSplinePlaybackController;
                    AppCamera::SdkModel::AppCameraSplinePlaybackWrapper m_appCamera;
                    int m_cameraHandle;
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    Eegeo::Location::NavigationService& m_navigationService;
                    AttractMode::SdkModel::States::AttractModeEnteringState m_enteringState;
                    AttractMode::SdkModel::States::AttractModeViewingState m_viewingState;
                    AttractMode::SdkModel::States::AttractModeExitingState m_exitingState;
                    const std::vector<Helpers::IStateMachineState*> m_subStates;
                    Helpers::StateMachine m_subStateMachine;
                    long long m_idleTimeAtStartMs;
                    Eegeo::Input::IUserIdleService& m_userIdleService;
                    Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;
                    VisualMap::SdkModel::IVisualMapService& m_visualMapService;
                    FlattenButton::SdkModel::IFlattenButtonModel& m_flattenButtonModel;

                    Eegeo::Geometry::CatmullRomSpline m_cameraTargetSpline;
                    Eegeo::Geometry::CatmullRomSpline m_cameraPositionSpline;

                    void ChangeToState(const AttractMode::SdkModel::States::State newState);
                    bool IsUserActive();
                    void InitialiseSplinePlaybackCameraState();

                public:
                    AttractState(AppModes::SdkModel::IAppModeModel& appModeModel,
                                 AppCamera::SdkModel::IAppCameraController& cameraController,
                                 Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController& cameraSplinePlaybackController,
                                 AppCamera::SdkModel::AppGlobeCameraWrapper& worldCameraController,
                                 const int worldCameraHandle,
                                 Eegeo::Resources::Interiors::InteriorsCameraController& interiorsCameraController,
                                 Eegeo::ITouchController& touchController,
                                 Eegeo::Location::ILocationService& locationService,
                                 Eegeo::Input::IUserIdleService& userIdleService,
                                 const std::vector<Eegeo::Space::LatLongAltitude>& cameraPositionSplinePoints,
                                 const std::vector<Eegeo::Space::LatLongAltitude>& cameraTargetSplinePoints,
                                 const float playbackSpeed,
                                 const Eegeo::Rendering::ScreenProperties& screenProperties,
                                 ExampleAppMessaging::TMessageBus& messageBus,
                                 Eegeo::Location::NavigationService& navigationService,
                                 Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                 VisualMap::SdkModel::IVisualMapService& visualMapService,
                                 FlattenButton::SdkModel::IFlattenButtonModel& flattenButtonModel);
                    ~AttractState();

                    void Enter(int previousState);
                    void Update(float dt);
                    void Exit(int nextState);

                    void NotifySubStateComplete();
                };
            }
        }
    }
}
