// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Menu.h"
#include "SearchResultOnMap.h"
#include "IScreenControlViewModel.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		class ISearchResultOnMapModule
		{
		public:
			virtual ~ISearchResultOnMapModule() { }

			virtual ISearchResultOnMapModel& GetSearchResultOnMapModel() const = 0;
		};
	}
}
