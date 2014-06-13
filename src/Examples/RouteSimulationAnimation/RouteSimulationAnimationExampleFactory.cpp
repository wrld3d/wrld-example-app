// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RouteSimulationAnimationExampleFactory.h"
#include "RouteSimulationAnimationExample.h"
#include "LocalAsyncTextureLoader.h"

using namespace Examples;

RouteSimulationAnimationExampleFactory::RouteSimulationAnimationExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* RouteSimulationAnimationExampleFactory::CreateExample() const
{
	Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraControllerFactory factory(m_world.GetTerrainHeightProvider(),
	        m_world.GetEnvironmentFlatteningService(),
	        m_world.GetResourceCeilingProvider(),
	        m_world.GetCollisionMeshResourceProvider());

	return new Examples::RouteSimulationAnimationExample(m_world.GetRouteService(),
	        m_world.GetRouteSimulationService(),
	        m_world.GetRouteSimulationViewService(),
	        m_globeCameraController,
	        m_world.GetCameraProvider(),
	        m_world.GetRenderContext().GetGLState(),
	        m_world.GetFileIO(),
	        m_world.GetLocalAsyncTextureLoader(),
	        factory,
	        m_world);
}

std::string RouteSimulationAnimationExampleFactory::ExampleName() const
{
	return Examples::RouteSimulationAnimationExample::GetName();
}
