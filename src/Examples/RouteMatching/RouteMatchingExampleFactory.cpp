//
//  RouteMatchingExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "RouteMatchingExampleFactory.h"
#include "RouteMatchingExample.h"

using namespace Examples;

RouteMatchingExampleFactory::RouteMatchingExampleFactory(Eegeo::EegeoWorld& world,
        const IRouteMatchingExampleViewFactory& routeMatchingViewFactory,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
	, m_routeMatchingViewFactory(routeMatchingViewFactory)
{

}

IExample* RouteMatchingExampleFactory::CreateExample() const
{
	return new Examples::RouteMatchingExample(m_world.GetRouteService(),
	        m_world,
	        m_routeMatchingViewFactory,
	        m_globeCameraController);
}

std::string RouteMatchingExampleFactory::ExampleName() const
{
	return Examples::RouteMatchingExample::GetName();
}
