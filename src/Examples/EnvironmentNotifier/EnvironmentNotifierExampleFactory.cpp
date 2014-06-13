// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "EnvironmentNotifierExampleFactory.h"
#include "EnvironmentNotifierExample.h"

using namespace Examples;

EnvironmentNotifierExampleFactory::EnvironmentNotifierExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* EnvironmentNotifierExampleFactory::CreateExample() const
{
	return new Examples::EnvironmentNotifierExample(m_world.GetRenderContext(),
	        m_world.GetTerrainStreaming(),
	        m_globeCameraController);
}

std::string EnvironmentNotifierExampleFactory::ExampleName() const
{
	return Examples::EnvironmentNotifierExample::GetName();
}

