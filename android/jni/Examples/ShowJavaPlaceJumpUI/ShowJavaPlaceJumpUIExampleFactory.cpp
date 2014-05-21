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
		AndroidNativeState& nativeState)
: m_exampleCameraJumpController(exampleCameraJumpController)
, m_nativeState(nativeState)
{

}

IExample* ShowJavaPlaceJumpUIExampleFactory::CreateExample() const
{
	return new Examples::ShowJavaPlaceJumpUIExample(
			m_nativeState,
			m_exampleCameraJumpController);
}
