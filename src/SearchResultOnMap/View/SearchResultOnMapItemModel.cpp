// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultOnMapItemModel.h"
#include "SearchResultModel.h"
#include "ISearchResultPoiViewModel.h"
#include "Logger.h"
#include "SearchResultOnMapItemModelSelectedMessage.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		SearchResultOnMapItemModel::SearchResultOnMapItemModel(Search::SearchResultModel& searchResultModel,
		        ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
			: m_searchResultModel(searchResultModel)
			, m_nativeToUiMessageBus(nativeToUiMessageBus)
		{

		}

		SearchResultOnMapItemModel::~SearchResultOnMapItemModel()
		{

		}

		void SearchResultOnMapItemModel::SelectPin()
		{
			m_nativeToUiMessageBus.Publish(SearchResultOnMapItemModelSelectedMessage(m_searchResultModel));
		}
	}
}
