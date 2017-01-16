// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "IStateMachineState.h"
#include "AppCamera.h"
#include "AppModes.h"
#include "IAppModeModel.h"
#include "Tours.h"
#include "ICallback.h"
#include "Interiors.h"
#include "InteriorsExplorer.h"
#include "AppCameraSplinePlaybackWrapper.h"
#include "IUserIdleService.h"
#include "CatmullRomSpline.h"
#include "BidirectionalBus.h"
#include "FlattenButton.h"
#include "NavigationService.h"
#include "AttractModeEnteringState.h"
#include "AttractModeViewingState.h"
#include "AttractModeExitingState.h"
#include "CameraTransitionService.h"
#include "ILocationService.h"
#include "Search.h"

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
                    enum States
                    {
                        EnterState = 0,
                        ViewState,
                        ExitState
                    };

                    AppModes::SdkModel::IAppModeModel& m_appModeModel;
                    AppCamera::SdkModel::IAppCameraController& m_cameraController;
                    Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController m_cameraSplinePlaybackController;
                    AppCamera::SdkModel::AppCameraSplinePlaybackWrapper m_appCamera;
                    int m_cameraHandle;
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    FlattenButton::SdkModel::IFlattenButtonModel& m_flattenButtonModel; 
                    Eegeo::Location::NavigationService& m_navigationService;
                    AttractMode::SdkModel::States::AttractModeEnteringState m_enteringState;
                    AttractMode::SdkModel::States::AttractModeViewingState m_viewingState;
                    AttractMode::SdkModel::States::AttractModeExitingState m_exitingState;
                    const std::vector<Helpers::IStateMachineState*> m_subStates;
                    Helpers::StateMachine m_subStateMachine;
                    long long m_idleTimeAtStartMs;
                    Eegeo::Input::IUserIdleService& m_userIdleService;
                    Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;

                    Eegeo::Geometry::CatmullRomSpline m_cameraTargetSpline;
                    Eegeo::Geometry::CatmullRomSpline m_cameraPositionSpline;

                    bool IsUserActive();
                    void InitialiseSplinePlaybackCameraState();

                public:
                    AttractState(AppModes::SdkModel::IAppModeModel& appModeModel,
                                 AppCamera::SdkModel::IAppCameraController& cameraController,
                                 AppCamera::SdkModel::AppGlobeCameraWrapper& worldCameraController,
                                 const int worldCameraHandle,
                                 Eegeo::ITouchController& touchController,
                                 Eegeo::Location::ILocationService& locationService,
                                 Eegeo::Input::IUserIdleService& userIdleService,
                                 Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                                 const std::vector<Eegeo::Space::LatLongAltitude>& cameraPositionSplinePoints,
                                 const std::vector<Eegeo::Space::LatLongAltitude>& cameraTargetSplinePoints,
                                 const float playbackSpeed,
                                 const Eegeo::Rendering::ScreenProperties& screenProperties,
                                 ExampleAppMessaging::TMessageBus& messageBus,
                                 FlattenButton::SdkModel::IFlattenButtonModel& flattenButtonModel,
                                 Eegeo::Location::NavigationService& navigationService,
                                 Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer);
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
