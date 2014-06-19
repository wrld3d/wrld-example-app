// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

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
