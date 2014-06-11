//
//  IRouteSimulationExampleViewFactory.h
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef ExampleApp_IRouteSimulationExampleViewFactory_h
#define ExampleApp_IRouteSimulationExampleViewFactory_h

#include "IRouteSimulationExampleView.h"

namespace Examples
{
class IRouteSimulationExampleViewFactory
{
public:

	virtual ~IRouteSimulationExampleViewFactory() { }

	virtual IRouteSimulationExampleView* CreateRouteSimulationExampleView() const = 0;
};
}



#endif
