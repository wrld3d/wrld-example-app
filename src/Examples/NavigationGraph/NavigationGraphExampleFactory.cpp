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

NavigationGraphExampleFactory::NavigationGraphExampleFactory(Eegeo::EegeoWorld& world)
: m_world(world)
{
    
}

IExample* NavigationGraphExampleFactory::CreateExample() const
{
    return new Examples::NavigationGraphExample(m_world.GetRenderContext(),
                                                m_world.GetNavigationGraphRepository());
}
