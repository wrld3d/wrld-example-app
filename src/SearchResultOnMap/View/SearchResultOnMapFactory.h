// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "ISearchResultOnMapFactory.h"
#include "SearchResultPoi.h"
#include "NativeToUiMessageBus.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		class SearchResultOnMapFactory : public ISearchResultOnMapFactory, private Eegeo::NonCopyable
		{
			ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;

		public:
			SearchResultOnMapFactory(ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);

			~SearchResultOnMapFactory();

			SearchResultOnMapItemModel* CreateSearchResultOnMapItemModel(Search::SearchResultModel& searchResultModel) const;
		};
	}
}
