// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include <algorithm>

#include "WorldState.h"
#include "IAppCameraController.h"
#include "TourService.h"
#include "IAppModeModel.h"
#include "InteriorSelectionModel.h"
#include "CameraHelpers.h"
#include "IAppCameraController.h"
#include "CameraState.h"
#include "RenderCamera.h"
#include "InteriorsCameraController.h"
#include "AttractState.h"
#include "AppCameraSplinePlaybackWrapper.h"
#include "IUserIdleService.h"
#include "LatLongAltitude.h"
#include "TimeHelpers.h"
#include "BidirectionalBus.h"
#include "WorldPinVisibility.h"
#include "FlattenButtonModel.h"
#include "NavigationService.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                AttractState::AttractState(AppModes::SdkModel::IAppModeModel& appModeModel,
                                           AppCamera::SdkModel::IAppCameraController& cameraController,
                                           Eegeo::ITouchController& touchController,
                                           Eegeo::Input::IUserIdleService& userIdleService,
                                           Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                                           const std::vector<Eegeo::Space::LatLongAltitude>& cameraPositionSplinePoints,
                                           const std::vector<Eegeo::Space::LatLongAltitude>& cameraTargetSplinePoints,
                                           const float playbackSpeed,
                                           const Eegeo::Rendering::ScreenProperties& screenProperties,
                                           ExampleAppMessaging::TMessageBus& messageBus,
                                           FlattenButton::SdkModel::IFlattenButtonModel& flattenButtonModel,
                                           Eegeo::Location::NavigationService& navigationService)
                : m_appModeModel(appModeModel)
                , m_cameraController(cameraController)
                , m_cameraSplinePlaybackController(resourceCeilingProvider)
                , m_appCamera(m_cameraSplinePlaybackController, touchController)
                , m_cameraHandle(m_cameraController.CreateCameraHandleFromController(m_appCamera))
                , m_messageBus(messageBus)
                , m_flattenButtonModel(flattenButtonModel)
                , m_navigationService(navigationService)
                , m_enteringState(*this, cameraController, m_cameraHandle)
                , m_viewingState(*this, m_cameraSplinePlaybackController)
                , m_subStates{ /*[States::EnterState] =*/ &m_enteringState,
                               /*[States::ViewState]  =*/ &m_viewingState }
                , m_subStateMachine(m_subStates)
                , m_idleTimeAtStartMs(0)
                , m_userIdleService(userIdleService)
                {
                    std::for_each(cameraPositionSplinePoints.begin(), cameraPositionSplinePoints.end(),
                                  [this](const Eegeo::Space::LatLongAltitude& p) { m_cameraPositionSpline.AddPoint(p.ToECEF()); });
                    std::for_each(cameraTargetSplinePoints.begin(), cameraTargetSplinePoints.end(),
                                  [this](const Eegeo::Space::LatLongAltitude& p) { m_cameraTargetSpline.AddPoint(p.ToECEF()); });

                    m_cameraPositionSpline.SetTimeParameterizationMethod(Eegeo::Geometry::TimeParameterizationMethod::Uniform);
                    m_cameraTargetSpline.SetTimeParameterizationMethod(Eegeo::Geometry::TimeParameterizationMethod::Uniform);
                    m_cameraSplinePlaybackController.SetSplines(&m_cameraPositionSpline, &m_cameraTargetSpline);

                    m_cameraSplinePlaybackController.SetPlaybackSpeed(playbackSpeed);
                    m_cameraSplinePlaybackController.SetLooped(true);
                    m_cameraSplinePlaybackController.UpdateScreenProperties(screenProperties);
                }

                AttractState::~AttractState()
                {
                    m_cameraController.RemoveCameraHandle(m_cameraHandle);
                }

                void AttractState::Enter(int previousState)
                {
                    m_messageBus.Publish(WorldPins::WorldPinsVisibilityMessage(WorldPins::SdkModel::WorldPinVisibility::None));
                    m_messageBus.Publish(GpsMarker::GpsMarkerVisibilityMessage(false));
                    m_flattenButtonModel.Unflatten();

                    InitialiseSplinePlaybackCameraState();
                    m_subStateMachine.StartStateMachine(States::EnterState);
                    m_idleTimeAtStartMs = m_userIdleService.GetUserIdleTimeMs();
                }

                void AttractState::Update(float dt)
                {
                    if (m_userIdleService.GetUserIdleTimeMs() < m_idleTimeAtStartMs)
                    {
                        m_appModeModel.SetAppMode(AppModes::SdkModel::WorldMode);
                    }
                    m_subStateMachine.Update(dt);
                }

                void AttractState::Exit(int nextState)
                {
                    m_subStateMachine.StopStateMachine();

                    m_messageBus.Publish(WorldPins::WorldPinsVisibilityMessage(WorldPins::SdkModel::WorldPinVisibility::All));
                    m_messageBus.Publish(GpsMarker::GpsMarkerVisibilityMessage(true));
                    m_navigationService.SetGpsMode(Eegeo::Location::NavigationService::GpsModeFollow);
                }

                void AttractState::NotifySubStateComplete()
                {
                    switch (m_subStateMachine.GetCurrentStateIndex())
                    {
                    case States::EnterState:
                        m_subStateMachine.ChangeToState(States::ViewState);
                        break;

                    case States::ViewState:
                    default:
                        Eegeo_ASSERT("Completion of invalid attract mode sub-state.");
                    }
                }

                void AttractState::InitialiseSplinePlaybackCameraState()
                {
                    m_cameraSplinePlaybackController.Play();
                    m_cameraSplinePlaybackController.Stop();
                }
            }
        }
    }
}
