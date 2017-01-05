// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

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
                    Eegeo::Input::IUserIdleService& m_userIdleService;
                    long long m_startTimeMs;
                    Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController m_cameraSplinePlaybackController;
                    Eegeo::Geometry::CatmullRomSpline m_cameraTargetSpline;
                    Eegeo::Geometry::CatmullRomSpline m_cameraPositionSpline;
                    AppCamera::SdkModel::AppCameraSplinePlaybackWrapper m_appCamera;
                    int m_cameraHandle;
                    ExampleAppMessaging::TMessageBus& m_messageBus;

                public:
                    AttractState(AppModes::SdkModel::IAppModeModel& appModeModel,
                                 AppCamera::SdkModel::IAppCameraController& cameraController,
                                 Eegeo::ITouchController& touchController,
                                 Eegeo::Input::IUserIdleService& userIdleService,
                                 Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                                 const long long attractModeTimeout,
                                 const std::vector<Eegeo::Space::LatLongAltitude>& cameraPositionSplinePoints,
                                 const std::vector<Eegeo::Space::LatLongAltitude>& cameraTargetSplinePoints,
                                 const Eegeo::Rendering::ScreenProperties& screenProperties,
                                 ExampleAppMessaging::TMessageBus& messageBus);
                    ~AttractState();

                    void Enter(int previousState);
                    void Update(float dt);
                    void Exit(int nextState);
                };
            }
        }
    }
}
