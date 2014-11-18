// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "NativeToUiMessageBus.h"
#include "ICallback.h"
#include "SearchResultOnMapItemModelSelectedMessage.h"
#include "ISearchResultPoiViewModel.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		class SearchResultOnMapItemModelSelectedObserver : private Eegeo::NonCopyable
		{
			SearchResultPoi::ISearchResultPoiViewModel& m_searchResultPoiViewModel;
			ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;
			Eegeo::Helpers::TCallback1<SearchResultOnMapItemModelSelectedObserver, const SearchResultOnMapItemModelSelectedMessage&> m_handlerBinding;

			void HandleReceivedSearchResultOnMapItemModelSelectedMessage(const SearchResultOnMapItemModelSelectedMessage& message);

		public:
			SearchResultOnMapItemModelSelectedObserver(SearchResultPoi::ISearchResultPoiViewModel& searchResultPoiViewModel,
			        ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);

			~SearchResultOnMapItemModelSelectedObserver();
		};
	}
}
