//
//  IRouteMatchingViewFactory.h
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef ExampleApp_IRouteMatchingViewFactory_h
#define ExampleApp_IRouteMatchingViewFactory_h

#include "IRouteMatchingView.h"

namespace Examples
{
    class IRouteMatchingViewFactory
    {
    public:
        
        virtual ~IRouteMatchingViewFactory() { }
        
        virtual IRouteMatchingView* CreateRouteMatchingView() const = 0;
    };
}

#endif
