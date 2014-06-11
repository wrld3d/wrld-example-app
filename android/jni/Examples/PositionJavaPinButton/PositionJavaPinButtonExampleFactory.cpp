/*
 * PositionJavaPinButtonExampleFactory.cpp
 *
 *  Created on: Dec 10, 2013
 *      Author: kimbleoperations
 */

#include "PositionJavaPinButtonExampleFactory.h"
#include "PositionJavaPinButtonExample.h"

using namespace Examples;

PositionJavaPinButtonExampleFactory::PositionJavaPinButtonExampleFactory(
    Eegeo::EegeoWorld& world,
    AndroidNativeState& nativeState,
    Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_nativeState(nativeState)
	, m_globeCameraController(globeCameraController)
{

}

IExample* PositionJavaPinButtonExampleFactory::CreateExample() const
{
	return new Examples::PositionJavaPinButtonExample(
	           m_world,
	           m_nativeState,
	           m_world.GetRenderContext(),
	           m_globeCameraController);
}

std::string PositionJavaPinButtonExampleFactory::ExampleName() const
{
	return Examples::PositionJavaPinButtonExample::GetName();
}
