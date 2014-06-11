//
//  ToggleTrafficExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "ToggleTrafficExampleFactory.h"
#include "ToggleTrafficExample.h"

using namespace Examples;

ToggleTrafficExampleFactory::ToggleTrafficExampleFactory(Eegeo::EegeoWorld& world,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
	: m_world(world)
	, m_globeCameraController(globeCameraController)
{

}

IExample* ToggleTrafficExampleFactory::CreateExample() const
{
	return new Examples::ToggleTrafficExample(m_world.GetTrafficSimulationController(),
	        m_globeCameraController);
}

std::string ToggleTrafficExampleFactory::ExampleName() const
{
	return Examples::ToggleTrafficExample::GetName();
}
