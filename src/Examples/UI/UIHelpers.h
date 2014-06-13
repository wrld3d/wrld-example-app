// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef ExampleApp_UIHelpers_h
#define ExampleApp_UIHelpers_h

#include "IUIActionHandler.h"
#include <vector>
#include <algorithm>

namespace Examples
{
template <typename T>
void RemoveFrom(std::vector<T>& vec, T item)
{
	typename std::vector<T>::iterator it = std::find(vec.begin(), vec.end(), item);

	if(it != vec.end())
	{
		vec.erase(it);
	}
}

void InvokeAllHandlers(std::vector<Examples::IUIActionHandler*>& handlers);
}

#endif
