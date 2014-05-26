//
//  RouteThicknessPolicyExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "RouteThicknessPolicyExampleFactory.h"
#include "RouteThicknessPolicyExample.h"
#include "LocalAsyncTextureLoader.h"

using namespace Examples;

RouteThicknessPolicyExampleFactory::RouteThicknessPolicyExampleFactory(Eegeo::EegeoWorld& world)
: m_world(world)
{
    
}

IExample* RouteThicknessPolicyExampleFactory::CreateExample() const
{
    return new Examples::RouteThicknessPolicyExample(m_world.GetRouteService(),
                                                     m_world.GetRenderContext(),
                                                     m_world);
}

std::string RouteThicknessPolicyExampleFactory::ExampleName() const
{
	return Examples::RouteThicknessPolicyExample::GetName();
}
