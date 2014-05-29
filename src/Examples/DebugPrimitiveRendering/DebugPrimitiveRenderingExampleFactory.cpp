//
//  DebugPrimitiveRenderingExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "DebugPrimitiveRenderingExampleFactory.h"
#include "DebugPrimitiveRenderingExample.h"

using namespace Examples;

DebugPrimitiveRenderingExampleFactory::DebugPrimitiveRenderingExampleFactory(Eegeo::EegeoWorld& world,
                                                                             Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
: m_world(world)
, m_globeCameraController(globeCameraController)
{
    
}

IExample* DebugPrimitiveRenderingExampleFactory::CreateExample() const
{
    return new Examples::DebugPrimitiveRenderingExample(m_world.GetDebugPrimitiveRenderer(),
                                                        m_globeCameraController);
}

std::string DebugPrimitiveRenderingExampleFactory::ExampleName() const
{
	return Examples::DebugPrimitiveRenderingExample::GetName();
}

