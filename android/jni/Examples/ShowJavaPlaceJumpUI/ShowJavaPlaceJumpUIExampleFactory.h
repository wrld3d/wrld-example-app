// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef SHOWJAVAPLACEJUMPUIEXAMPLEFACTORY_H_
#define SHOWJAVAPLACEJUMPUIEXAMPLEFACTORY_H_

#include "IExampleFactory.h"
#include "IExample.h"
#include "ExampleCameraJumpController.h"
#include "AndroidNativeState.h"
#include "GlobeCameraController.h"

namespace Examples
{
class ShowJavaPlaceJumpUIExampleFactory : public IExampleFactory
{
	ExampleCameraJumpController& m_exampleCameraJumpController;
	Eegeo::Camera::GlobeCamera::GlobeCameraController& m_cameraController;
	AndroidNativeState& m_nativeState;

public:
	ShowJavaPlaceJumpUIExampleFactory(
	    ExampleCameraJumpController& exampleCameraJumpController,
	    Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController,
	    AndroidNativeState& nativeState);

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}


#endif /* SHOWJAVAPLACEJUMPUIEXAMPLEFACTORY_H_ */
