//
//  WebRequestExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "WebRequestExampleFactory.h"
#include "WebRequestExample.h"

using namespace Examples;

WebRequestExampleFactory::WebRequestExampleFactory(Eegeo::EegeoWorld& world)
: m_world(world)
{
    
}

IExample* WebRequestExampleFactory::CreateExample() const
{
    return new Examples::WebRequestExample(m_world.GetWebRequestFactory());
}
