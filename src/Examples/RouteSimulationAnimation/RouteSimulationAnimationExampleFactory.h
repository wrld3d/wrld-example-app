// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__RouteSimulationAnimationExampleFactory__
#define __ExampleApp__RouteSimulationAnimationExampleFactory__

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"

namespace Examples
{
class RouteSimulationAnimationExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
	Eegeo::Camera::GlobeCamera::GlobeCameraController& m_globeCameraController;
	Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraControllerFactory* m_pRouteSimulationGlobeCameraControllerFactory;

public:
	RouteSimulationAnimationExampleFactory(Eegeo::EegeoWorld& world,
	                                       Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController);

	~RouteSimulationAnimationExampleFactory();

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}

#endif /* defined(__ExampleApp__RouteSimulationAnimationExampleFactory__) */
