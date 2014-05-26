//
//  PinOverModelExampleFactory.h
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__PinOverModelExampleFactory__
#define __ExampleApp__PinOverModelExampleFactory__

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"

namespace Examples
{
    class PinOverModelExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        
    public:
        PinOverModelExampleFactory(Eegeo::EegeoWorld& world);

        std::string ExampleName() const;
        
        IExample* CreateExample() const;
    };
}


#endif /* defined(__ExampleApp__PinOverModelExampleFactory__) */
