/*
 * ExampleCameraJumpController.cpp
 *
 *  Created on: Nov 6, 2013
 */

#include "ExampleCameraJumpController.h"
#include "GlobeCameraController.h"
#include "GlobeCameraTouchController.h"
#include "CameraHelpers.h"
#include "EcefTangentBasis.h"
#include "LatLongAltitude.h"
#include "ITouchController.h"

ExampleCameraJumpController::ExampleCameraJumpController(
		Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController,
		Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
: m_cameraController(cameraController)
, m_cameraTouchController(cameraTouchController)
{

}

void ExampleCameraJumpController::JumpTo(const Eegeo::Space::LatLongAltitude& interestPoint, float cameraHeadingDegrees, float cameraDistanceToInterest)
{
	// calculate a new interest coordinate basis
	Eegeo::Space::EcefTangentBasis interestBasis;
	Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(interestPoint.ToECEF(), cameraHeadingDegrees, interestBasis);

	// command the camera controller to set its view point
	m_cameraController.SetView(interestBasis, cameraDistanceToInterest);

	// reset the camera touch controller, so any camera movement due to touch input is cancelled
	m_cameraTouchController.Reset();
}

void ExampleCameraJumpController::JumpTo(const Eegeo::Space::LatLongAltitude& interestPoint)
{
	Eegeo::Space::EcefTangentBasis interestBasis = m_cameraController.GetInterestBasis();
	interestBasis.SetPoint(interestPoint.ToECEF());
	m_cameraController.SetInterestBasis(interestBasis);
	m_cameraTouchController.Reset();
}

bool ExampleCameraJumpController::CanJump() const
{
	// In this example, always allow camera jumps
	return true;
}

