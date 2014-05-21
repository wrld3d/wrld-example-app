//
//  EnvironmentNotifierExampleFactory.h
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__EnvironmentNotifierExampleFactory__
#define __ExampleApp__EnvironmentNotifierExampleFactory__

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"

namespace Examples
{
    class EnvironmentNotifierExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        
    public:
        EnvironmentNotifierExampleFactory(Eegeo::EegeoWorld& world);
        
        IExample* CreateExample() const;
    };
}

#endif /* defined(__ExampleApp__EnvironmentNotifierExampleFactory__) */
