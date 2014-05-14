

#ifndef __examples_ExampleCameraJumpController__
#define __examples_ExampleCameraJumpController__

#include "ICameraJumpController.h"
#include "GlobeCamera.h"

/*!
 *  \brief Implements ICameraJumpController for the camera controller used in example apps
 *
 *  ExampleCameraJumpController implements ICameraJumpContoller by taking a dependency on
 *  the camera controller objects used in example apps.
 */
class ExampleCameraJumpController : public Eegeo::Camera::ICameraJumpController
{
public:
	ExampleCameraJumpController(
			Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController,
			Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);

	virtual void JumpTo(const Eegeo::Space::LatLongAltitude& interestPoint, float cameraHeadingDegrees, float cameraDistanceToInterest);
	virtual void JumpTo(const Eegeo::Space::LatLongAltitude& interestPoint);
	virtual bool CanJump() const;

private:
	Eegeo::Camera::GlobeCamera::GlobeCameraController& m_cameraController;
	Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_cameraTouchController;
};

#endif // __examples_ExampleCameraJumpController__
