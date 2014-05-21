//
//  DebugPrimitiveRenderingExampleFactory.h
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__DebugPrimitiveRenderingExampleFactory__
#define __ExampleApp__DebugPrimitiveRenderingExampleFactory__

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"

namespace Examples
{
    class DebugPrimitiveRenderingExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        
    public:
        DebugPrimitiveRenderingExampleFactory(Eegeo::EegeoWorld& world);
        
        IExample* CreateExample() const;
    };
}


#endif /* defined(__ExampleApp__DebugPrimitiveRenderingExampleFactory__) */
