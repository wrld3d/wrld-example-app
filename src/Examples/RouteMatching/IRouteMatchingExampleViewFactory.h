//
//  IRouteMatchingExampleViewFactory.h
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef ExampleApp_IRouteMatchingExampleViewFactory_h
#define ExampleApp_IRouteMatchingExampleViewFactory_h

#include "IRouteMatchingExampleView.h"

namespace Examples
{
    class IRouteMatchingExampleViewFactory
    {
    public:
        
        virtual ~IRouteMatchingExampleViewFactory() { }
        
        virtual IRouteMatchingExampleView* CreateRouteMatchingExampleView() const = 0;
    };
}

#endif
