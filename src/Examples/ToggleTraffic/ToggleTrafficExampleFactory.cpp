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

ToggleTrafficExampleFactory::ToggleTrafficExampleFactory(Eegeo::EegeoWorld& world)
: m_world(world)
{
    
}

IExample* ToggleTrafficExampleFactory::CreateExample() const
{
    return new Examples::ToggleTrafficExample(m_world.GetTrafficSimulationController());
}
