//
//  EnvironmentFlatteningExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "EnvironmentFlatteningExampleFactory.h"
#include "EnvironmentFlatteningExample.h"

using namespace Examples;

EnvironmentFlatteningExampleFactory::EnvironmentFlatteningExampleFactory(Eegeo::EegeoWorld& world)
: m_world(world)
{
    
}

IExample* EnvironmentFlatteningExampleFactory::CreateExample() const
{
    return new Examples::EnvironmentFlatteningExample(m_world.GetEnvironmentFlatteningService());
}
