// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "DebugPrimitiveRenderingExampleFactory.h"
#include "DebugPrimitiveRenderingExample.h"
#include "ICameraProvider.h"

using namespace Examples;

DebugPrimitiveRenderingExampleFactory::DebugPrimitiveRenderingExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* DebugPrimitiveRenderingExampleFactory::CreateExample() const
{
	return new Examples::DebugPrimitiveRenderingExample(m_world.GetDebugRenderer(),
            m_world.GetCameraProvider().GetRenderCamera(),
	        m_globeCameraController);
}

std::string DebugPrimitiveRenderingExampleFactory::ExampleName() const
{
	return Examples::DebugPrimitiveRenderingExample::GetName();
}

