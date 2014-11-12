// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultOnMapItemModel.h"
#include "SearchResultModel.h"
#include "ISearchResultPoiViewModel.h"
#include "Logger.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		SearchResultOnMapItemModel::SearchResultOnMapItemModel(Search::SearchResultModel& searchResultModel,
		        SearchResultPoi::ISearchResultPoiViewModel& searchResultPoiViewModel)
			: m_searchResultModel(searchResultModel)
			, m_searchResultPoiViewModel(searchResultPoiViewModel)
		{

		}

		SearchResultOnMapItemModel::~SearchResultOnMapItemModel()
		{

		}

		void SearchResultOnMapItemModel::SelectPin()
		{
			if(!m_searchResultPoiViewModel.IsOpen())
			{
				EXAMPLE_LOG("Selected search result: %s\n", m_searchResultModel.GetTitle().c_str());
				m_searchResultPoiViewModel.Open(m_searchResultModel);
			}
		}
	}
}
