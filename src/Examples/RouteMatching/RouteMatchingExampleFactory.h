//
//  RouteMatchingExampleFactory.h
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__RouteMatchingExampleFactory__
#define __ExampleApp__RouteMatchingExampleFactory__

#include "IExampleFactory.h"
#include "IExample.h"
#include "EegeoWorld.h"
#include "IRouteMatchingExampleViewFactory.h"

namespace Examples
{
    class RouteMatchingExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        const IRouteMatchingExampleViewFactory& m_routeMatchingViewFactory;
        
    public:
        RouteMatchingExampleFactory(Eegeo::EegeoWorld& world,
                                    const IRouteMatchingExampleViewFactory& routeMatchingViewFactory);
        
        std::string ExampleName() const;

        IExample* CreateExample() const;
    };
}

#endif /* defined(__ExampleApp__RouteMatchingExampleFactory__) */
