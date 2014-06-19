// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

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
