// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CameraTransitionExampleFactory.h"
#include "CameraTransitionExample.h"

using namespace Examples;

CameraTransitionExampleFactory::CameraTransitionExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* CameraTransitionExampleFactory::CreateExample() const
{
	return new Examples::CameraTransitionExample(m_globeCameraController,
	        m_world.GetInterestPointProvider());
}

std::string CameraTransitionExampleFactory::ExampleName() const
{
	return Examples::CameraTransitionExample::GetName();
}

