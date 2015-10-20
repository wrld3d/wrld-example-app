// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TransitionToWorldPointStage.h"
#include "CameraHelpers.h"
#include "EcefTangentBasis.h"
#include "GpsGlobeCameraController.h"
#include "TerrainHeightProvider.h"
#include "EarthConstants.h"
#include "Quaternion.h"

namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {
            namespace
            {
                Eegeo::v3 ComputeHeadingVector(const Eegeo::dv3& interestPoint, float heading)
                {
                    Eegeo::v3 interestForward(0,1,0);
                    Eegeo::dv3 interestEcefUp = interestPoint.Norm();
                    Eegeo::v3 interestUp = interestEcefUp.ToSingle();
                    
                    Eegeo::v3 interestRight = Eegeo::v3::Cross(interestUp, interestForward);
                    interestRight = interestRight.Norm();
                    
                    interestForward = Eegeo::v3::Cross(interestRight, interestUp);
                    interestForward = interestForward.Norm();
                    
                    Eegeo::Quaternion rotation;
                    rotation.Set(interestUp, heading);
                    interestForward = rotation.RotatePoint(interestForward);
                    
                    return interestForward;
                }
            }
            
            TransitionToWorldPointStage::TransitionToWorldPointStage(Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& gpsGlobeCameraController,
                                                                     Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
                                                                     const Eegeo::dv3& newInterestPoint,
                                                                     float distanceFromInterest,
                                                                     float newHeadingRadians,
                                                                     bool jumpIfFar)
            : m_gpsGlobeCameraController(gpsGlobeCameraController)
            , m_terrainHeightProvider(terrainHeightProvider)
            , m_jumpIfFar(jumpIfFar)
            {
                const Eegeo::Space::EcefTangentBasis& currentInterestBasis = m_gpsGlobeCameraController.GetInterestBasis();
                m_startTransitionInterestPointEcef = currentInterestBasis.GetPointEcef();
                m_startInterestDistance = m_gpsGlobeCameraController.GetDistanceToInterest();
                m_startInterestHeading = Eegeo::Camera::CameraHelpers::GetAbsoluteBearingRadians(currentInterestBasis.GetPointEcef(),
                                                                                                 currentInterestBasis.GetForward());;
                
                m_endTransitionInterestPointEcef = newInterestPoint;
                m_endInterestDistance = distanceFromInterest;
                m_endInterestHeading = newHeadingRadians;
                
                m_transitionTime = 0.0f;
                
                const float CAMERA_TRANSITION_SPEED_IN_METERS_PER_SECOND = 1000.0f;
                const float MIN_TRANSITION_TIME = 0.5f;
                const float MAX_TRANSITION_TIME = 2.0f;
                float distance = (m_endTransitionInterestPointEcef - m_startTransitionInterestPointEcef).ToSingle().Length();
                
                m_transitionDuration = Eegeo::Clamp(distance/CAMERA_TRANSITION_SPEED_IN_METERS_PER_SECOND, MIN_TRANSITION_TIME, MAX_TRANSITION_TIME);
                
                if(std::abs(m_endInterestHeading - m_startInterestHeading) > Eegeo::Math::kPI)
                {
                    if(m_endInterestHeading > m_startInterestHeading)
                        m_endInterestHeading -= 2.f * Eegeo::Math::kPI;
                    else
                        m_startInterestHeading -= 2.f * Eegeo::Math::kPI;
                }
            }
            
            void TransitionToWorldPointStage::Start()
            {
            }
            
            void TransitionToWorldPointStage::Update(float dt)
            {
                if(m_jumpIfFar && ShouldJumpTo(m_endTransitionInterestPointEcef))
                {
                    m_transitionTime = m_transitionDuration;
                    return;
                }
                
                m_transitionTime += dt;
                float transitionParam = Eegeo::Math::SmoothStep(0.f, 1.f, m_transitionTime / m_transitionDuration);
                
                float interpolatedDistance = Eegeo::Math::Lerp(m_startInterestDistance, m_endInterestDistance, transitionParam);
                Eegeo::dv3 interpolatedInterestPosition = Eegeo::dv3::Lerp(m_startTransitionInterestPointEcef, m_endTransitionInterestPointEcef, transitionParam);
                float currentAssumedAltitude = 0;
                
                m_terrainHeightProvider.TryGetHeight(interpolatedInterestPosition, 0, currentAssumedAltitude);
                
                if(interpolatedInterestPosition.Length() < Eegeo::Space::EarthConstants::Radius + currentAssumedAltitude)
                {
                    interpolatedInterestPosition = interpolatedInterestPosition.Norm() * (Eegeo::Space::EarthConstants::Radius + currentAssumedAltitude);
                }
                
                float interpolatedHeading = Eegeo::Math::Lerp<float>(m_startInterestHeading, m_endInterestHeading, transitionParam);
                Eegeo::v3 interpolatedHeadingVector = ComputeHeadingVector(interpolatedInterestPosition, interpolatedHeading);
                
                Eegeo::Space::EcefTangentBasis newInterestBasis(interpolatedInterestPosition, interpolatedHeadingVector);
                m_gpsGlobeCameraController.SetView(newInterestBasis, interpolatedDistance);
            }
            
            void TransitionToWorldPointStage::End()
            {
                float currentAssumedAltitude = 0;
                m_terrainHeightProvider.TryGetHeight(m_endTransitionInterestPointEcef, 0, currentAssumedAltitude);
                if(m_endTransitionInterestPointEcef.Length() < Eegeo::Space::EarthConstants::Radius + currentAssumedAltitude)
                {
                    m_endTransitionInterestPointEcef = m_endTransitionInterestPointEcef.Norm() * (Eegeo::Space::EarthConstants::Radius + currentAssumedAltitude);
                }
                
                Eegeo::Space::EcefTangentBasis newInterestBasis;
                Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(m_endTransitionInterestPointEcef,
                                                                                  Eegeo::Math::Rad2Deg(m_endInterestHeading),
                                                                                  newInterestBasis);
                m_gpsGlobeCameraController.SetView(newInterestBasis, m_endInterestDistance);
            }
            
            const bool TransitionToWorldPointStage::StageIsComplete() const
            {
                return m_transitionTime >= m_transitionDuration;
            }
            
            bool TransitionToWorldPointStage::ShouldJumpTo(Eegeo::dv3& newInterestPoint)
            {
                const double MAX_CAMERA_TRANSITION_DISTANCE = 5000;
                Eegeo::dv3 currentInterestPoint = m_gpsGlobeCameraController.GetEcefInterestPoint();
                double distance = (newInterestPoint - currentInterestPoint).Length();
                return distance > MAX_CAMERA_TRANSITION_DISTANCE;
            }

            const bool TransitionToWorldPointStage::StageHasFailed() const
            {
                return false;
            }
        }
    }
}