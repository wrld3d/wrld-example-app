// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RouteThicknessPolicyExampleFactory.h"
#include "RouteThicknessPolicyExample.h"
#include "LocalAsyncTextureLoader.h"

using namespace Examples;

RouteThicknessPolicyExampleFactory::RouteThicknessPolicyExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* RouteThicknessPolicyExampleFactory::CreateExample() const
{
	return new Examples::RouteThicknessPolicyExample(m_world.GetRouteService(),
	        m_world.GetRenderContext(),
	        m_world,
	        m_globeCameraController);
}

std::string RouteThicknessPolicyExampleFactory::ExampleName() const
{
	return Examples::RouteThicknessPolicyExample::GetName();
}
