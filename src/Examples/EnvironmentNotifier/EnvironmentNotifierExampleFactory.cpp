//
//  EnvironmentNotifierExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "EnvironmentNotifierExampleFactory.h"
#include "EnvironmentNotifierExample.h"

using namespace Examples;

EnvironmentNotifierExampleFactory::EnvironmentNotifierExampleFactory(Eegeo::EegeoWorld& world)
: m_world(world)
{
    
}

IExample* EnvironmentNotifierExampleFactory::CreateExample() const
{
    return new Examples::EnvironmentNotifierExample(m_world.GetRenderContext(),
                                                    m_world.GetTerrainStreaming());
}

std::string EnvironmentNotifierExampleFactory::ExampleName() const
{
	return Examples::EnvironmentNotifierExample::GetName();
}

