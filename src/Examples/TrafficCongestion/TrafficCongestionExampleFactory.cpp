//
//  TrafficCongestionExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "TrafficCongestionExampleFactory.h"
#include "TrafficCongestionExample.h"

using namespace Examples;

TrafficCongestionExampleFactory::TrafficCongestionExampleFactory(Eegeo::EegeoWorld& world,
                                                                 Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
: m_world(world)
, m_globeCameraController(globeCameraController)
{
    
}

IExample* TrafficCongestionExampleFactory::CreateExample() const
{
    return new Examples::TrafficCongestionExample(m_world.GetTrafficCongestionService(),
                                                  m_globeCameraController);
}

std::string TrafficCongestionExampleFactory::ExampleName() const
{
	return Examples::TrafficCongestionExample::GetName();
}
