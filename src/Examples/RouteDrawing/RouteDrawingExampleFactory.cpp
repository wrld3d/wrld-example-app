//
//  RouteDrawingExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "RouteDrawingExampleFactory.h"
#include "RouteDrawingExample.h"

using namespace Examples;

RouteDrawingExampleFactory::RouteDrawingExampleFactory(Eegeo::EegeoWorld& world,
                                                       Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
: m_world(world)
, m_globeCameraController(globeCameraController)
{
    
}

IExample* RouteDrawingExampleFactory::CreateExample() const
{
    return new Examples::RouteDrawingExample(m_world.GetRouteService(),
                                             m_world,
                                             m_globeCameraController);
}

std::string RouteDrawingExampleFactory::ExampleName() const
{
	return Examples::RouteDrawingExample::GetName();
}

