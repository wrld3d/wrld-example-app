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

			void HandleReceivedSearchResultOnMapItemModelSelectedMessage(const SearchResultOnMapItemModelSelectedMessage& message)
			{
				if(!m_searchResultPoiViewModel.IsOpen())
				{
					m_searchResultPoiViewModel.Open(message.GetModel());
				}
			}

		public:
			SearchResultOnMapItemModelSelectedObserver(SearchResultPoi::ISearchResultPoiViewModel& searchResultPoiViewModel,
			        ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
				: m_searchResultPoiViewModel(searchResultPoiViewModel)
				, m_nativeToUiMessageBus(nativeToUiMessageBus)
				, m_handlerBinding(this, &SearchResultOnMapItemModelSelectedObserver::HandleReceivedSearchResultOnMapItemModelSelectedMessage)
			{
				m_nativeToUiMessageBus.Subscribe(m_handlerBinding);
			}

			~SearchResultOnMapItemModelSelectedObserver()
			{
				m_nativeToUiMessageBus.Unsubscribe(m_handlerBinding);
			}
		};
	}
}
