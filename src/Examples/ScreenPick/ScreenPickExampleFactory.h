//
//  ScreenPickExampleFactory.h
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__ScreenPickExampleFactory__
#define __ExampleApp__ScreenPickExampleFactory__

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"

namespace Examples
{
    class ScreenPickExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        
    public:
        ScreenPickExampleFactory(Eegeo::EegeoWorld& world);
        
        IExample* CreateExample() const;
    };
}

#endif /* defined(__ExampleApp__ScreenPickExampleFactory__) */
