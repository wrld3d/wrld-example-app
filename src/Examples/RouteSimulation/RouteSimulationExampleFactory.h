//
//  RouteSimulationExampleFactory.h
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__RouteSimulationExampleFactory__
#define __ExampleApp__RouteSimulationExampleFactory__

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"
#include "IRouteSimulationExampleViewFactory.h"

namespace Examples
{
class RouteSimulationExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
	const IRouteSimulationExampleViewFactory& m_routeSimulationViewFactory;
	Eegeo::Camera::GlobeCamera::GlobeCameraController& m_globeCameraController;

public:
	RouteSimulationExampleFactory(Eegeo::EegeoWorld& world,
	                              Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController,
	                              const IRouteSimulationExampleViewFactory& routeSimulationViewFactory);

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}


#endif /* defined(__ExampleApp__RouteSimulationExampleFactory__) */
