// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "AttractState.h"
#include "AttractModeExitingState.h"
#include "CameraHelpers.h"
#include "CameraTransitionService.h"
#include "CatmullRomSpline.h"
#include "EcefTangentBasis.h"
#include "GpsGlobeCameraController.h"
#include "MathFunc.h"
#include "IAppCameraController.h"
#include "ILocationService.h"
#include "TimeHelpers.h"

#include <algorithm>
#include <numeric>

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

                    float TransitionDuration(const float distToTarget, const float approximateMaxDistance)
                    {
                        const float MaxTransitionTime = 3.0f;
                        const float MinTransitionTime = MaxTransitionTime * 0.3f;
                        const float TransitionTimeRange =  MaxTransitionTime - MinTransitionTime;

                        return MinTransitionTime + Eegeo::Clamp(distToTarget / approximateMaxDistance, 0.0f, 1.0f) * TransitionTimeRange;
                    }

                    double ApproximateMaxDistance(const Eegeo::dv3 targetPoint, const std::vector<Eegeo::Geometry::CatmullRomSplinePoint>& points)
                    {
                        return std::accumulate(points.begin(), points.end(), 0.0,
                            [=](const double maxDistToTarget, const Eegeo::Geometry::CatmullRomSplinePoint p)
                            {
                                const double distToTarget = (p.Position - targetPoint).Length();
                                return std::max<double>(distToTarget, maxDistToTarget);
                            });
                    }
                }

                AttractModeExitingState::AttractModeExitingState(AppModes::States::SdkModel::AttractState& attractState,
                                                                 AppCamera::SdkModel::IAppCameraController& cameraController,
                                                                 Eegeo::Location::ILocationService& locationService,
                                                                 const int worldCameraHandle,
                                                                 AppCamera::SdkModel::AppGlobeCameraWrapper& worldCameraController,
                                                                 Eegeo::Resources::Interiors::InteriorsCameraController& interiorsCameraController,
                                                                 Eegeo::Geometry::CatmullRomSpline& cameraPositionPoints)
                : m_attractState(attractState)
                , m_cameraController(cameraController)
                , m_locationService(locationService)
                , m_worldCameraHandle(worldCameraHandle)
                , m_worldCameraController(worldCameraController)
                , m_interiorsCameraController(interiorsCameraController)
                , m_cameraPositionPoints(cameraPositionPoints)
                {
                }

                void AttractModeExitingState::Enter(int previousState)
                {
                    if (previousState == States::EnterState)
                    {
                        m_cameraController.SetTransitionTimeMultiplier(5.0f);
                    }
                    else
                    {
                        Eegeo::Space::LatLong gpsLatLong(0.0, 0.0);
                        const Eegeo::Space::LatLong targetLocation(m_locationService.GetLocation(gpsLatLong)
                            ? gpsLatLong
                            : Eegeo::Space::LatLong::FromECEF(m_worldCameraController.GetCameraState().InterestPointEcef()));
                        double headingDegrees;
                        if (!m_locationService.GetHeadingDegrees(headingDegrees))
                        {
                            headingDegrees = m_cameraController.GetHeadingDegrees();
                        }
                        Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& globeCameraController = m_worldCameraController.GetGlobeCameraController();

                        double altitude;
                        if (m_locationService.GetAltitude(altitude) == false)
                        {
                            altitude = globeCameraController.GetDistanceToInterest();
                        }
                        globeCameraController.SetView(gpsLatLong.GetLatitudeInDegrees(),
                                                      gpsLatLong.GetLongitudeInDegrees(),
                                                      headingDegrees,
                                                      altitude);

                        const Eegeo::dv3 currentLocation = m_cameraController.GetCameraState().LocationEcef();
                        const float distanceToTarget = (currentLocation - targetLocation.ToECEF()).Length();
                        const float approximateMaxDistance = static_cast<float>(ApproximateMaxDistance(targetLocation.ToECEF(), m_cameraPositionPoints.GetPoints()));
                        const float transitionDuration = TransitionDuration(distanceToTarget, approximateMaxDistance);
                        m_cameraController.TransitionToCameraWithHandle(m_worldCameraHandle, JumpDistanceThreshold, transitionDuration);
                    }
                }
                
                void AttractModeExitingState::Update(float dt)
                {
                    if (!m_cameraController.IsTransitionInFlight())
                    {
                        m_interiorsCameraController.SetHeading(m_cameraController.GetHeadingDegrees());
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
