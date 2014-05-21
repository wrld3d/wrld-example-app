//
//  RouteThicknessPolicyExampleFactory.h
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__RouteThicknessPolicyExampleFactory__
#define __ExampleApp__RouteThicknessPolicyExampleFactory__

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"

namespace Examples
{
    class RouteThicknessPolicyExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        
    public:
        RouteThicknessPolicyExampleFactory(Eegeo::EegeoWorld& world);
        
        IExample* CreateExample() const;
    };
}

#endif /* defined(__ExampleApp__RouteThicknessPolicyExampleFactory__) */
