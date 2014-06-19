// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__RouteMatchingExampleFactory__
#define __ExampleApp__RouteMatchingExampleFactory__

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"
#include "IRouteMatchingExampleViewFactory.h"

namespace Examples
{
class RouteMatchingExampleFactory : public IExampleFactory
{
	Eegeo::EegeoWorld& m_world;
	const IRouteMatchingExampleViewFactory& m_routeMatchingViewFactory;
	Eegeo::Camera::GlobeCamera::GlobeCameraController& m_globeCameraController;

public:
	RouteMatchingExampleFactory(Eegeo::EegeoWorld& world,
	                            const IRouteMatchingExampleViewFactory& routeMatchingViewFactory,
	                            Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController);

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}

#endif /* defined(__ExampleApp__RouteMatchingExampleFactory__) */
