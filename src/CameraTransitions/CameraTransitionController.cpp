// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CameraTransitionController.h"
#include "EcefTangentBasis.h"
#include "GpsGlobeCameraController.h"
#include "CameraHelpers.h"
#include "MathFunc.h"
#include "EarthConstants.h"
#include "Quaternion.h"
#include "NavigationService.h"

namespace ExampleApp
{
    namespace CameraTransitions
    {
        
        Eegeo::v3 ComputeHeadingVector(Eegeo::dv3 interestPosition, float heading)
        {
            Eegeo::v3 interestForward(0,1,0);
            Eegeo::dv3 interestEcefUp = interestPosition.Norm();
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
        
        CameraTransitionController::CameraTransitionController(Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& cameraController,
                                                               Eegeo::Location::NavigationService& navigationService)
        : m_cameraController(cameraController)
        , m_navigationService(navigationService)
        , m_transitionTime(0.f)
        , m_transitionDuration(0.f)
        , m_isTransitioning(false)
        {
            
        }
        
        void CameraTransitionController::StartTransitionTo(Eegeo::dv3 newInterestPoint, double distanceFromInterest, bool jumpIfFar)
        {
            const Eegeo::Space::EcefTangentBasis& cameraInterestBasis = m_cameraController.GetInterestBasis();
            
            float bearingRadians = Eegeo::Camera::CameraHelpers::GetAbsoluteBearingRadians(cameraInterestBasis.GetPointEcef(),
                                                                                           cameraInterestBasis.GetForward());
            
            StartTransitionTo(newInterestPoint, distanceFromInterest, bearingRadians, jumpIfFar);
        }
        
        void CameraTransitionController::StartTransitionTo(Eegeo::dv3 newInterestPoint, double distanceFromInterest, float newHeadingRadians, bool jumpIfFar)
        {
            if(IsTransitioning())
            {
                StopCurrentTransition();
            }
            
            m_navigationService.SetGpsMode(Eegeo::Location::NavigationService::GpsModeOff);
            
            if(jumpIfFar && ShouldJumpTo(newInterestPoint))
            {
                Eegeo::Space::EcefTangentBasis newInterestBasis;
                Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(newInterestPoint,
                                                                                  Eegeo::Math::Rad2Deg(newHeadingRadians),
                                                                                  newInterestBasis);
                m_cameraController.SetView(newInterestBasis, distanceFromInterest);
                return;
            }
            
            const Eegeo::Space::EcefTangentBasis& currentInterestBasis = m_cameraController.GetInterestBasis();
            m_startTransitionInterestPointEcef = currentInterestBasis.GetPointEcef();
            m_startInterestDistance = m_cameraController.GetDistanceToInterest();
            m_startInterestHeading = Eegeo::Camera::CameraHelpers::GetAbsoluteBearingRadians(currentInterestBasis.GetPointEcef(),
                                                                                             currentInterestBasis.GetForward());;
            
            m_endTransitionInterestPointEcef = newInterestPoint;
            m_endInterestDistance = distanceFromInterest;
            m_endInterestHeading = newHeadingRadians;
            
            m_transitionTime = 0.0f;
            
            const float CAMERA_TRANSITION_SPEED_IN_METERS_PER_SECOND = 1000.0f;
            const float MIN_TRANSITION_TIME = 0.5f;
            const float MAX_TRANSITION_TIME = 2.0f;
            float distance = (m_endTransitionInterestPointEcef - m_startTransitionInterestPointEcef).Length();
            
            m_transitionDuration = Eegeo::Clamp(distance/CAMERA_TRANSITION_SPEED_IN_METERS_PER_SECOND, MIN_TRANSITION_TIME, MAX_TRANSITION_TIME);
            
            m_isTransitioning = true;
            
            if(abs(m_endInterestHeading - m_startInterestHeading) > M_PI)
            {
                if(m_endInterestHeading > m_startInterestHeading)
                    m_endInterestHeading -= M_2_PI;
                else
                    m_startInterestHeading -= M_2_PI;
            }
        }
        
        bool CameraTransitionController::ShouldJumpTo(Eegeo::dv3& newInterestPoint)
        {
            const double MAX_CAMERA_TRANSITION_DISTANCE = 5000;
            Eegeo::dv3 currentInterestPoint = m_cameraController.GetEcefInterestPoint();
            double distance = (newInterestPoint - currentInterestPoint).Length();
            return distance > MAX_CAMERA_TRANSITION_DISTANCE;
        }
        
        void CameraTransitionController::StopCurrentTransition()
        {
            m_isTransitioning = false;
            m_transitionDuration = 0.f;
            m_transitionTime = 0.f;
        }
        
        void CameraTransitionController::Update(float dt)
        {
            if(!IsTransitioning())
            {
                return;
            }
            
            m_transitionTime += dt;
            double transitionParam = Eegeo::Math::SmoothStep(0.f, 1.f, m_transitionTime / m_transitionDuration);
        
            float interpolatedDistance = Eegeo::Math::Lerp(m_startInterestDistance, m_endInterestDistance, transitionParam);
            Eegeo::dv3 interpolatedInterestPosition = Eegeo::dv3::Lerp(m_startTransitionInterestPointEcef, m_endTransitionInterestPointEcef, transitionParam);
            if(interpolatedInterestPosition.LengthSq() < Eegeo::Space::EarthConstants::RadiusSquared)
            {
                interpolatedInterestPosition = interpolatedInterestPosition.Norm() * Eegeo::Space::EarthConstants::Radius;
            }
            
            float interpolatedHeading = Eegeo::Math::Lerp<float>(m_startInterestHeading, m_endInterestHeading, transitionParam);
            Eegeo::v3 interpolatedHeadingVector = ComputeHeadingVector(interpolatedInterestPosition, interpolatedHeading);
            
            Eegeo::Space::EcefTangentBasis newInterestBasis(interpolatedInterestPosition, interpolatedHeadingVector);
            m_cameraController.SetView(newInterestBasis, interpolatedDistance);
            
            if(transitionParam >= 1.f)
            {
                StopCurrentTransition();
            }
        }
    }
}
