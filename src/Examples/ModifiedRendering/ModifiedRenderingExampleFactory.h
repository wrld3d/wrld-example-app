//
//  ModifiedRenderingExampleFactory.h
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__ModifiedRenderingExampleFactory__
#define __ExampleApp__ModifiedRenderingExampleFactory__

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"

namespace Examples
{
    class ModifiedRenderingExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        
    public:
        ModifiedRenderingExampleFactory(Eegeo::EegeoWorld& world);
        
        IExample* CreateExample() const;
    };
}

#endif /* defined(__ExampleApp__ModifiedRenderingExampleFactory__) */
