// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "AttractState.h"
#include "AttractModeExitingState.h"
#include "CameraHelpers.h"
#include "CameraTransitionService.h"
#include "EcefTangentBasis.h"
#include "GpsGlobeCameraController.h"
#include "IAppCameraController.h"
#include "ILocationService.h"
#include "TimeHelpers.h"

namespace ExampleApp
{
    namespace AttractMode
    {
        namespace SdkModel
        {
            namespace States
            {
                namespace
                {
                    const double JumpDistanceThreshold = 25000.0;
                    const float TransitionDuration = 3.0f;
                }

                AttractModeExitingState::AttractModeExitingState(AppModes::States::SdkModel::AttractState& attractState,
                                                                 AppCamera::SdkModel::IAppCameraController& cameraController,
                                                                 Eegeo::Location::ILocationService& locationService,
                                                                 const int worldCameraHandle,
                                                                 AppCamera::SdkModel::AppGlobeCameraWrapper& worldCameraController)
                : m_attractState(attractState)
                , m_cameraController(cameraController)
                , m_locationService(locationService)
                , m_worldCameraHandle(worldCameraHandle)
                , m_worldCameraController(worldCameraController)
                {
                }

                void AttractModeExitingState::Enter(int previousState)
                {
                    Eegeo::Space::LatLong gpsLatLong(0.0, 0.0);
                    const Eegeo::dv3 targetLocation(m_locationService.GetLocation(gpsLatLong)
                        ? gpsLatLong.ToECEF()
                        : m_worldCameraController.GetCameraState().InterestPointEcef());
                    double headingDegrees;
                    if (!m_locationService.GetHeadingDegrees(headingDegrees))
                    {
                        headingDegrees = m_cameraController.GetHeadingDegrees();
                    }
                    Eegeo::Space::EcefTangentBasis newInterestBasis;
                    Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(targetLocation,
                                                                                      m_cameraController.GetHeadingDegrees(),
                                                                                      newInterestBasis);
                    m_worldCameraController.GetGlobeCameraController().SetInterestBasis(newInterestBasis);
                    m_cameraController.TransitionToCameraWithHandle(m_worldCameraHandle, JumpDistanceThreshold, TransitionDuration);
                }
                
                void AttractModeExitingState::Update(float dt)
                {
                    if (!m_cameraController.IsTransitionInFlight())
                    {
                        m_attractState.NotifySubStateComplete();
                    }
                }
                
                void AttractModeExitingState::Exit(int nextState)
                {
                }
            }
        }
    }
}
