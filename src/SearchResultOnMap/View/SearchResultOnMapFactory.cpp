// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultOnMapFactory.h"
#include "SearchResultOnMapItemModel.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		SearchResultOnMapFactory::SearchResultOnMapFactory(ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
			: m_nativeToUiMessageBus(nativeToUiMessageBus)
		{

		}

		SearchResultOnMapFactory::~SearchResultOnMapFactory()
		{

		}

		SearchResultOnMapItemModel* SearchResultOnMapFactory::CreateSearchResultOnMapItemModel(Search::SearchResultModel& searchResultModel) const
		{
			return Eegeo_NEW(SearchResultOnMapItemModel(searchResultModel,
			                 m_nativeToUiMessageBus));
		}
	}
}
