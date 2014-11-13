// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "ISearchResultOnMapInFocusViewModel.h"
#include "ICallback.h"
#include "NativeToUiMessageBus.h"
#include "SearchResultGainedFocusMessage.h"
#include "SearchResultLostFocusMessage.h"
#include "SearchResultInFocusChangedLocationMessage.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		class SearchResultOnMapInFocusObserver : private Eegeo::NonCopyable
		{
			ISearchResultOnMapInFocusViewModel& m_searchResultOnMapInFocusViewModel;
			ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;
			Eegeo::Helpers::TCallback1<SearchResultOnMapInFocusObserver, const SearchResultGainedFocusMessage&> m_gainedFocusHandler;
			Eegeo::Helpers::TCallback1<SearchResultOnMapInFocusObserver, const SearchResultLostFocusMessage&> m_lostFocusHandler;
			Eegeo::Helpers::TCallback1<SearchResultOnMapInFocusObserver, const SearchResultInFocusChangedLocationMessage&> m_focusScreenLocationUpdatedHandler;

			void HandleReceivedSearchResultGainedFocusMessage(const SearchResultGainedFocusMessage& message);

			void HandleReceivedSearchResultLostFocusMessage(const SearchResultLostFocusMessage& message);

			void HandleReceivedSearchResultInFocusChangedLocationMessage(const SearchResultInFocusChangedLocationMessage& message);

		public:
			SearchResultOnMapInFocusObserver(
			    ISearchResultOnMapInFocusViewModel& searchResultOnMapInFocusViewModel,
			    ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);

			~SearchResultOnMapInFocusObserver();
		};
	}
}
