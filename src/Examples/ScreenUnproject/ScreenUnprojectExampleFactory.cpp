// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ScreenUnprojectExampleFactory.h"
#include "ScreenUnprojectExample.h"

using namespace Examples;

ScreenUnprojectExampleFactory::ScreenUnprojectExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* ScreenUnprojectExampleFactory::CreateExample() const
{
	return new Examples::ScreenUnprojectExample(m_world.GetRenderContext(),
	        m_world.GetCameraProvider(),
	        m_world.GetTerrainHeightProvider(),
	        m_globeCameraController);
}

std::string ScreenUnprojectExampleFactory::ExampleName() const
{
	return Examples::ScreenUnprojectExample::GetName();
}
