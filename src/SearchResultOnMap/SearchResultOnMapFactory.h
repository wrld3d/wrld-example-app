// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "ISearchResultOnMapFactory.h"
#include "SearchResultPoi.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		class SearchResultOnMapFactory : public ISearchResultOnMapFactory, private Eegeo::NonCopyable
		{
			SearchResultPoi::ISearchResultPoiViewModel& m_searchResultPoiViewModel;

		public:
			SearchResultOnMapFactory(SearchResultPoi::ISearchResultPoiViewModel& searchResultPoiViewModel);

			~SearchResultOnMapFactory();

			SearchResultOnMapItemModel* CreateSearchResultOnMapItemModel(Search::SearchResultModel& searchResultModel) const;
		};
	}
}
