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

#include <vector>

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                enum AttractModeSubStates
                {
                    Enter = 0,
                    View
                };

                class AttractState : public Helpers::IStateMachineState
                {
                private:
                    AppCamera::SdkModel::IAppCameraController& m_cameraController;
                    Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController m_cameraSplinePlaybackController;
                    AppCamera::SdkModel::AppCameraSplinePlaybackWrapper m_appCamera;
                    int m_cameraHandle;
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    FlattenButton::SdkModel::IFlattenButtonModel& m_flattenButtonModel; 
                    Eegeo::Location::NavigationService& m_navigationService;
                    AttractMode::SdkModel::States::AttractModeEnteringState m_enteringState;
                    AttractMode::SdkModel::States::AttractModeViewingState m_viewingState;
                    const std::vector<Helpers::IStateMachineState*> m_subStates;
                    Helpers::StateMachine m_subStateMachine;

                    Eegeo::Geometry::CatmullRomSpline m_cameraTargetSpline;
                    Eegeo::Geometry::CatmullRomSpline m_cameraPositionSpline;

                    void InitialiseSplinePlaybackCameraState();

                public:
                    AttractState(AppModes::SdkModel::IAppModeModel& appModeModel,
                                 AppCamera::SdkModel::IAppCameraController& cameraController,
                                 Eegeo::ITouchController& touchController,
                                 Eegeo::Input::IUserIdleService& userIdleService,
                                 Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                                 const std::vector<Eegeo::Space::LatLongAltitude>& cameraPositionSplinePoints,
                                 const std::vector<Eegeo::Space::LatLongAltitude>& cameraTargetSplinePoints,
                                 const Eegeo::Rendering::ScreenProperties& screenProperties,
                                 ExampleAppMessaging::TMessageBus& messageBus,
                                 FlattenButton::SdkModel::IFlattenButtonModel& flattenButtonModel,
                                 Eegeo::Location::NavigationService& navigationService);
                    ~AttractState();

                    void Enter(int previousState);
                    void Update(float dt);
                    void Exit(int nextState);
                };
            }
        }
    }
}
