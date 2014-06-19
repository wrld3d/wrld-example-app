// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef ExampleApp_IRouteMatchingExampleView_h
#define ExampleApp_IRouteMatchingExampleView_h

#include "Types.h"
#include "IUIActionHandler.h"

namespace Examples
{
class IRouteMatchingExampleView
{
public:
	virtual ~IRouteMatchingExampleView() { }

	virtual void AddMatchingToggledHandler(IUIActionHandler& handler)=0;

	virtual void RemoveMatchingToggledHandler(IUIActionHandler& handler)=0;
};
}

#endif
