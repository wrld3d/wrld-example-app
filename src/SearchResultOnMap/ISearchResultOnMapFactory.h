// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Search.h"
#include "SearchResultOnMap.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		class ISearchResultOnMapFactory
		{
		public:
			virtual ~ISearchResultOnMapFactory() { }

			virtual SearchResultOnMapItemModel* CreateSearchResultOnMapItemModel(Search::SearchResultModel& searchResultModel) const = 0;
		};
	}
}
