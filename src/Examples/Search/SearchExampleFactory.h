//
//  SearchExampleFactory.h
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__SearchExampleFactory__
#define __ExampleApp__SearchExampleFactory__

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"

namespace Examples
{
    class SearchExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        
    public:
        SearchExampleFactory(Eegeo::EegeoWorld& world);
        
        IExample* CreateExample() const;
    };
}

#endif /* defined(__ExampleApp__SearchExampleFactory__) */
