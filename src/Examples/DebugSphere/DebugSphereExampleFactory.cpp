//
//  DebugSphereExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "DebugSphereExampleFactory.h"
#include "DebugSphereExample.h"
#include "IInterestPointProvider.h"
#include "LatLongAltitude.h"

using namespace Examples;

DebugSphereExampleFactory::DebugSphereExampleFactory(Eegeo::EegeoWorld& world)
: m_world(world)
{
    
}

IExample* DebugSphereExampleFactory::CreateExample() const
{
    return new Examples::DebugSphereExample(m_world.GetRenderContext(),
                                            Eegeo::Space::LatLongAltitude::FromECEF(m_world.GetInterestPointProvider().GetEcefInterestPoint()));
}

std::string DebugSphereExampleFactory::ExampleName() const
{
	return Examples::DebugSphereExample::GetName();
}


