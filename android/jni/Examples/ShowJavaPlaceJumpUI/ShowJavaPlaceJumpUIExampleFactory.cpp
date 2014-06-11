/*
 * ShowJavaPlaceJumpUIExampleFactory.cpp
 *
 *  Created on: Dec 10, 2013
 *      Author: kimbleoperations
 */

#include "ShowJavaPlaceJumpUIExampleFactory.h"
#include "ShowJavaPlaceJumpUIExample.h"

using namespace Examples;

ShowJavaPlaceJumpUIExampleFactory::ShowJavaPlaceJumpUIExampleFactory(
    ExampleCameraJumpController& exampleCameraJumpController,
    Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController,
    AndroidNativeState& nativeState)
	: m_exampleCameraJumpController(exampleCameraJumpController)
	, m_cameraController(cameraController)
	, m_nativeState(nativeState)
{

}

IExample* ShowJavaPlaceJumpUIExampleFactory::CreateExample() const
{
	return new Examples::ShowJavaPlaceJumpUIExample(
	           m_nativeState,
	           m_cameraController,
	           m_exampleCameraJumpController);
}

std::string ShowJavaPlaceJumpUIExampleFactory::ExampleName() const
{
	return Examples::ShowJavaPlaceJumpUIExample::GetName();
}
