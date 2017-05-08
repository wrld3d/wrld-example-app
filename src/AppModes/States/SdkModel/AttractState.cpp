// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include <algorithm>

#include "WorldState.h"
#include "IAppCameraController.h"
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
#include "NavigationService.h"
#include "CameraTransitionService.h"
#include "ILocationService.h"
#include "ISearchQueryPerformer.h"
#include "IVisualMapService.h"
#include "AttractModeStates.h"

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
                                           FlattenButton::SdkModel::IFlattenButtonModel& flattenButtonModel)
                : m_appModeModel(appModeModel)
                , m_cameraController(cameraController)
                , m_cameraSplinePlaybackController(cameraSplinePlaybackController)
                , m_appCamera(m_cameraSplinePlaybackController, touchController)
                , m_cameraHandle(m_cameraController.CreateCameraHandleFromController(m_appCamera))
                , m_messageBus(messageBus)
                , m_navigationService(navigationService)
                , m_enteringState(*this, cameraController, m_cameraHandle)
                , m_viewingState(m_cameraSplinePlaybackController)
                , m_exitingState(*this,
                                 cameraController,
                                 locationService,
                                 worldCameraHandle,
                                 worldCameraController,
                                 interiorsCameraController,
                                 m_cameraPositionSpline)
                , m_subStates{ &m_enteringState,
                               &m_viewingState,
                               &m_exitingState }
                , m_subStateMachine(m_subStates)
                , m_idleTimeAtStartMs(0)
                , m_userIdleService(userIdleService)
                , m_searchQueryPerformer(searchQueryPerformer)
                , m_visualMapService(visualMapService)
                , m_flattenButtonModel(flattenButtonModel)
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
                    m_flattenButtonModel.Unflatten();
                    m_visualMapService.SetVisualMapState("Summer", "DayDefault", false);
                    m_messageBus.Publish(WorldPins::WorldPinsVisibilityMessage(WorldPins::SdkModel::WorldPinVisibility::None));
                    m_messageBus.Publish(GpsMarker::GpsMarkerVisibilityMessage(false));

                    const AttractMode::SdkModel::States::State initialState = AttractMode::SdkModel::States::State::EnterState;
                    InitialiseSplinePlaybackCameraState();
                    m_subStateMachine.StartStateMachine(initialState);
                    m_idleTimeAtStartMs = m_userIdleService.GetUserIdleTimeMs();
                    m_messageBus.Publish(AttractMode::AttractModeStateChangedMessage(initialState));

                    m_searchQueryPerformer.RemoveSearchQueryResults();
                }

                void AttractState::Update(float dt)
                {
                    m_subStateMachine.Update(dt);
                    if (IsUserActive() && m_subStateMachine.GetCurrentStateIndex() != AttractMode::SdkModel::States::State::ExitState)
                    {
                        ChangeToState(AttractMode::SdkModel::States::State::ExitState);
                    }
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
                    case AttractMode::SdkModel::States::State::EnterState:
                        ChangeToState(AttractMode::SdkModel::States::State::ViewState);
                        break;

                    case AttractMode::SdkModel::States::State::ExitState:
                        m_appModeModel.SetAppMode(AppModes::SdkModel::WorldMode);
                        break;

                    case AttractMode::SdkModel::States::State::ViewState:
                    default:
                        Eegeo_ASSERT("Completion of invalid attract mode sub-state.");
                    }

                }

                void AttractState::ChangeToState(const AttractMode::SdkModel::States::State newState)
                {
                    m_subStateMachine.ChangeToState(newState);
                    m_messageBus.Publish(AttractMode::AttractModeStateChangedMessage(newState));
                }

                bool AttractState::IsUserActive()
                {
                    return m_userIdleService.GetUserIdleTimeMs() < m_idleTimeAtStartMs;
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
