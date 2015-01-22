// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "SearchResultPoiViewIncludes.h"

namespace ExampleApp
{
	namespace SearchResultPoi
	{
		class ISearchResultPoiViewModule
		{
		public:
			virtual ~ISearchResultPoiViewModule() { }

			virtual SearchResultPoiViewController& GetSearchResultPoiViewController() const = 0;

			virtual SearchResultPoiView& GetSearchResultPoiView() const = 0;
		};
	}
}
