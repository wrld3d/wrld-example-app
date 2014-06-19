// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RouteSimulationAnimationExampleFactory.h"
#include "RouteSimulationAnimationExample.h"
#include "LocalAsyncTextureLoader.h"

using namespace Examples;

RouteSimulationAnimationExampleFactory::RouteSimulationAnimationExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
	, m_pRouteSimulationGlobeCameraControllerFactory(NULL)
{
	m_pRouteSimulationGlobeCameraControllerFactory = new Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraControllerFactory
	(                                                                                                                                        m_world.GetTerrainHeightProvider(),
	        m_world.GetEnvironmentFlatteningService(),
	        m_world.GetResourceCeilingProvider(),
	        m_world.GetCollisionMeshResourceProvider()
	);
}


RouteSimulationAnimationExampleFactory::~RouteSimulationAnimationExampleFactory()
{
	delete m_pRouteSimulationGlobeCameraControllerFactory;
}

IExample* RouteSimulationAnimationExampleFactory::CreateExample() const
{
	return new Examples::RouteSimulationAnimationExample(m_world.GetRouteService(),
	        m_world.GetRouteSimulationService(),
	        m_world.GetRouteSimulationViewService(),
	        m_globeCameraController,
	        m_world.GetCameraProvider(),
	        m_world.GetRenderContext().GetGLState(),
	        m_world.GetFileIO(),
	        m_world.GetLocalAsyncTextureLoader(),
	        *m_pRouteSimulationGlobeCameraControllerFactory,
	        m_world);
}

std::string RouteSimulationAnimationExampleFactory::ExampleName() const
{
	return Examples::RouteSimulationAnimationExample::GetName();
}
