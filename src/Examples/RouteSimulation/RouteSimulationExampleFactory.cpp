// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RouteSimulationExampleFactory.h"
#include "RouteSimulationExample.h"
#include "RenderContext.h"
#include "LocalAsyncTextureLoader.h"

using namespace Examples;

RouteSimulationExampleFactory::RouteSimulationExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController,
        const IRouteSimulationExampleViewFactory& routeSimulationViewFactory)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
	, m_routeSimulationViewFactory(routeSimulationViewFactory)
{

}

IExample* RouteSimulationExampleFactory::CreateExample() const
{
	Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraControllerFactory factory(m_world.GetTerrainHeightProvider(),
	        m_world.GetEnvironmentFlatteningService(),
	        m_world.GetResourceCeilingProvider(),
	        m_world.GetCollisionMeshResourceProvider());

	return new Examples::RouteSimulationExample(m_world.GetRouteService(),
	        m_world.GetRouteSimulationService(),
	        m_world.GetRouteSimulationViewService(),
	        m_world.GetRenderContext().GetGLState(),
	        m_world.GetFileIO(),
	        m_world.GetLocalAsyncTextureLoader(),
	        m_globeCameraController,
	        m_world.GetInterestPointProvider(),
	        factory,
	        m_routeSimulationViewFactory,
	        m_world);
}

std::string RouteSimulationExampleFactory::ExampleName() const
{
	return Examples::RouteSimulationExample::GetName();
}


