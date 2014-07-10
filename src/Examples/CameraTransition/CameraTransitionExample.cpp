// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "EegeoWorld.h"
#include "CameraTransitionExample.h"
#include "Quaternion.h"
#include "MathFunc.h"
#include "CameraHelpers.h"
#include "NavigationService.h"
#include "GlobeCameraController.h"
#include "EcefTangentBasis.h"
#include <math.h>
#include "ICameraProvider.h"
#include "IInterestPointProvider.h"
#include "GlobeCameraTouchController.h"
#include "EarthConstants.h"
#include "LatLongAltitude.h"

namespace Examples
{
Eegeo::v3 ComputeHeadingVector(Eegeo::dv3 interestPosition, float heading)
{
	Eegeo::v3 m_heading(0,1,0);
	Eegeo::dv3 interestEcefUp = interestPosition.Norm();
	Eegeo::v3 m_interestUp = Eegeo::v3(interestEcefUp.GetX(), interestEcefUp.GetY(), interestEcefUp.GetZ());

	Eegeo::v3 m_interestRight = Eegeo::v3::Cross(m_interestUp, m_heading);
	m_interestRight = m_interestRight.Norm();

	m_heading = Eegeo::v3::Cross(m_interestRight, m_interestUp);
	m_heading = m_heading.Norm();

	Eegeo::Quaternion headingRot;
	headingRot.Set(m_interestUp, heading);
	m_heading = headingRot.RotatePoint(m_heading);

	return m_heading;
}

CameraTransitioner::CameraTransitioner(
    Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController,
    Eegeo::Location::IInterestPointProvider& interestPointProvider
)
	: m_cameraController(cameraController)
	, m_interestPointProvider(interestPointProvider)
	, m_isTransitioning(false)
	, m_transitionDuration(0.f)
	, m_transitionTime(0.f)
{

}

void CameraTransitioner::StartTransitionTo(Eegeo::dv3 newInterestPoint, double distanceFromInterest, bool jumpIfFarAway)
{
	const Eegeo::Space::EcefTangentBasis& cameraInterestBasis = m_cameraController.GetInterestBasis();

	float bearingRadians = Eegeo::Camera::CameraHelpers::GetAbsoluteBearingRadians(cameraInterestBasis.GetPointEcef(), cameraInterestBasis.GetForward());

	StartTransitionTo(newInterestPoint, distanceFromInterest, bearingRadians, jumpIfFarAway);
}

bool CameraTransitioner::ShouldJumpTo(Eegeo::dv3 newInterestPoint)
{
	const double MAX_CAMERA_TRANSITION_DISTANCE = 5000;
	Eegeo::dv3 currentInterestPoint = m_interestPointProvider.GetEcefInterestPoint();
	double distance = (newInterestPoint - currentInterestPoint).Length();
	return distance > MAX_CAMERA_TRANSITION_DISTANCE;
}

void CameraTransitioner::StartTransitionTo(Eegeo::dv3 newInterestPoint, double distanceFromInterest, float newHeading, bool jumpIfFarAway)
{
	if(IsTransitioning())
	{
		StopCurrentTransition();
	}

	if(jumpIfFarAway && ShouldJumpTo(newInterestPoint))
	{
		Eegeo::Space::EcefTangentBasis newInterestBasis;
		Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(newInterestPoint, Eegeo::Math::Rad2Deg(newHeading), newInterestBasis);
		m_cameraController.SetView(newInterestBasis, distanceFromInterest);
		StopCurrentTransition();
		return;
	}

	const Eegeo::Space::EcefTangentBasis& currentInterestBasis = m_cameraController.GetInterestBasis();
	m_startTransitionInterestPoint = currentInterestBasis.GetPointEcef();
	m_startInterestDistance = m_cameraController.GetDistanceToInterest();

	float bearingRadians = Eegeo::Camera::CameraHelpers::GetAbsoluteBearingRadians(currentInterestBasis.GetPointEcef(), currentInterestBasis.GetForward());
	m_startTransitionHeading = bearingRadians;
	m_endTransitionHeading = newHeading;
	m_endTransitionInterestPoint = newInterestPoint;
	m_endInterestDistance = distanceFromInterest;
	m_transitionTime = 0.f;

	const float CAMERA_TRANSITION_SPEED_IN_METERS_PER_SECOND = 100.0f;
	const float MIN_TRANSITION_TIME = 2.0f;
	const float MAX_TRANSITION_TIME = 10.0f;
	float distance = (m_endTransitionInterestPoint - m_startTransitionInterestPoint).Length();

	m_transitionDuration = Eegeo::Clamp(distance/CAMERA_TRANSITION_SPEED_IN_METERS_PER_SECOND, MIN_TRANSITION_TIME, MAX_TRANSITION_TIME);

	m_isTransitioning = true;

	if(abs(m_endTransitionHeading - m_startTransitionHeading) > M_PI)
	{
		if(m_endTransitionHeading > m_startTransitionHeading)
			m_endTransitionHeading -= 2 * M_PI;
		else
			m_startTransitionHeading -= 2 * M_PI;
	}

}

void CameraTransitioner::Update(float dt)
{
	if(!IsTransitioning())
	{
		return;
	}

	m_transitionTime += dt;
	double transitionParam = Eegeo::Math::SmoothStep(0.0, 1.0, m_transitionTime / m_transitionDuration);

	float interpolatedDistance = Eegeo::Math::Lerp(m_startInterestDistance, m_endInterestDistance, transitionParam);
	Eegeo::dv3 interpolatedInterestPosition = Eegeo::dv3::Lerp(m_startTransitionInterestPoint, m_endTransitionInterestPoint, transitionParam);
	if(interpolatedInterestPosition.LengthSq() < Eegeo::Space::EarthConstants::RadiusSquared)
	{
		interpolatedInterestPosition = interpolatedInterestPosition.Norm() * Eegeo::Space::EarthConstants::Radius;
	}

	float interpolatedHeading = ((1-transitionParam) * m_startTransitionHeading) + (transitionParam * m_endTransitionHeading);

	Eegeo::v3 interpolatedHeadingVector = ComputeHeadingVector(interpolatedInterestPosition, interpolatedHeading);

	Eegeo::Space::EcefTangentBasis newInterestBasis(interpolatedInterestPosition, interpolatedHeadingVector);
	m_cameraController.SetView(newInterestBasis, interpolatedDistance);

	if(transitionParam >= 1.f)
	{
		StopCurrentTransition();
	}
}

void CameraTransitioner::StopCurrentTransition()
{
	m_isTransitioning = false;
	m_transitionTime = 0.f;
	m_transitionDuration = 0.f;
}

CameraTransitionExample::CameraTransitionExample(Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController,
        Eegeo::Location::IInterestPointProvider& interestPointProvider)
	: m_cameraController(cameraController)
	, m_interestPointProvider(interestPointProvider)
	, m_transitioner(cameraController, interestPointProvider)
	, m_firstPoint(true)
	,m_globeCameraStateRestorer(cameraController)
{
}

void CameraTransitionExample::Transition()
{
	const float interestPointDistanceMetres = 1800.f;
	if (m_firstPoint)
	{
		Eegeo::Space::LatLong transitionDestinationLatLong = Eegeo::Space::LatLong::FromDegrees(37.718739, -122.500771);
		m_transitioner.StartTransitionTo(transitionDestinationLatLong.ToECEF(), interestPointDistanceMetres, false);
	}
	else
	{
		Eegeo::Space::LatLong transitionDestinationLatLong = Eegeo::Space::LatLong::FromDegrees(37.779547, -122.398805);
		m_transitioner.StartTransitionTo(transitionDestinationLatLong.ToECEF(), interestPointDistanceMetres, false);
	}
	m_firstPoint = !m_firstPoint;
}

void CameraTransitionExample::EarlyUpdate(float dt)
{
	if (!m_transitioner.IsTransitioning())
	{
		Transition();
	}
	m_transitioner.Update(dt);
}

void CameraTransitionExample::UpdateCamera(Eegeo::Camera::GlobeCamera::GlobeCameraController* pGlobeCameraController,
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController* pCameraTouchController,
        float dt)
{
	// Do not update touch events or the globe controller if the transition controller is working
	if (!m_transitioner.IsTransitioning())
	{
		pCameraTouchController->Update(dt);
		pGlobeCameraController->Update(dt);
	}
}
}
