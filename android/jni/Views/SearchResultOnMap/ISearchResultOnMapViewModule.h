// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "SearchResultOnMapViewIncludes.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		class ISearchResultOnMapViewModule
		{
		public:
			virtual ~ISearchResultOnMapViewModule() { }

			virtual SearchResultOnMapViewController& GetSearchResultOnMapViewController() const = 0;
		};
	}
}
