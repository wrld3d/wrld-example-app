//
//  IRouteMatchingExampleView.h
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

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
