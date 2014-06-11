//
//  UIHelpers.cpp
//  ExampleApp
//
//  Created by Scott on 20/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "UIHelpers.h"

namespace Examples
{
void InvokeAllHandlers(std::vector<Examples::IUIActionHandler*>& handlers)
{
	for(std::vector<Examples::IUIActionHandler*>::iterator it = handlers.begin(); it != handlers.end(); ++ it)
	{
		Examples::IUIActionHandler& handler = **it;
		handler();
	}
}
}
