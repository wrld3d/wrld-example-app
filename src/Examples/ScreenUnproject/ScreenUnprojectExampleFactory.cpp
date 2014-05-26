//
//  ScreenUnprojectExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "ScreenUnprojectExampleFactory.h"
#include "ScreenUnprojectExample.h"

using namespace Examples;

ScreenUnprojectExampleFactory::ScreenUnprojectExampleFactory(Eegeo::EegeoWorld& world)
: m_world(world)
{
    
}

IExample* ScreenUnprojectExampleFactory::CreateExample() const
{
    return new Examples::ScreenUnprojectExample(m_world.GetRenderContext(),
                                                m_world.GetCameraProvider(),
                                                m_world.GetTerrainHeightProvider());
}

std::string ScreenUnprojectExampleFactory::ExampleName() const
{
	return Examples::ScreenUnprojectExample::GetName();
}
