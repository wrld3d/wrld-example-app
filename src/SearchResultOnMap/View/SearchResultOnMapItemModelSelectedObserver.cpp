// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultOnMapItemModelSelectedObserver.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		SearchResultOnMapItemModelSelectedObserver::SearchResultOnMapItemModelSelectedObserver(SearchResultPoi::ISearchResultPoiViewModel& searchResultPoiViewModel,
				ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
			: m_searchResultPoiViewModel(searchResultPoiViewModel)
			, m_nativeToUiMessageBus(nativeToUiMessageBus)
			, m_handlerBinding(this, &SearchResultOnMapItemModelSelectedObserver::HandleReceivedSearchResultOnMapItemModelSelectedMessage)
		{
			m_nativeToUiMessageBus.Subscribe(m_handlerBinding);
		}

		SearchResultOnMapItemModelSelectedObserver::~SearchResultOnMapItemModelSelectedObserver()
		{
			m_nativeToUiMessageBus.Unsubscribe(m_handlerBinding);
		}

		void SearchResultOnMapItemModelSelectedObserver::HandleReceivedSearchResultOnMapItemModelSelectedMessage(const SearchResultOnMapItemModelSelectedMessage& message)
		{
			if(!m_searchResultPoiViewModel.IsOpen())
			{
				m_searchResultPoiViewModel.Open(message.GetModel());
			}
		}
	}
}
