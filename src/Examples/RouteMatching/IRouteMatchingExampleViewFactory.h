// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

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
