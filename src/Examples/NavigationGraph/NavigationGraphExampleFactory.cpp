//
//  NavigationGraphExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "NavigationGraphExampleFactory.h"
#include "NavigationGraphExample.h"

using namespace Examples;

NavigationGraphExampleFactory::NavigationGraphExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* NavigationGraphExampleFactory::CreateExample() const
{
	return new Examples::NavigationGraphExample(m_world.GetRenderContext(),
	        m_world.GetNavigationGraphRepository(),
	        m_globeCameraController);
}

std::string NavigationGraphExampleFactory::ExampleName() const
{
	return Examples::NavigationGraphExample::GetName();
}
