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

	void HandleReceivedSearchResultGainedFocusMessage(const SearchResultGainedFocusMessage& message)
	{
		m_searchResultOnMapInFocusViewModel.Open(message.FocussedModel(), message.ScreenLocation());
	}

	void HandleReceivedSearchResultLostFocusMessage(const SearchResultLostFocusMessage& message)
	{
		m_searchResultOnMapInFocusViewModel.Close();
	}

	void HandleReceivedSearchResultInFocusChangedLocationMessage(const SearchResultInFocusChangedLocationMessage& message)
	{
		m_searchResultOnMapInFocusViewModel.UpdateScreenLocation(message.ScreenLocation());
	}

public:
	SearchResultOnMapInFocusObserver(
	    ISearchResultOnMapInFocusViewModel& searchResultOnMapInFocusViewModel,
	    ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
		: m_searchResultOnMapInFocusViewModel(searchResultOnMapInFocusViewModel)
		, m_nativeToUiMessageBus(nativeToUiMessageBus)
		, m_gainedFocusHandler(this, &SearchResultOnMapInFocusObserver::HandleReceivedSearchResultGainedFocusMessage)
		, m_lostFocusHandler(this, &SearchResultOnMapInFocusObserver::HandleReceivedSearchResultLostFocusMessage)
		, m_focusScreenLocationUpdatedHandler(this, &SearchResultOnMapInFocusObserver::HandleReceivedSearchResultInFocusChangedLocationMessage)
	{
		m_nativeToUiMessageBus.Subscribe(m_gainedFocusHandler);
		m_nativeToUiMessageBus.Subscribe(m_lostFocusHandler);
		m_nativeToUiMessageBus.Subscribe(m_focusScreenLocationUpdatedHandler);
	}

	~SearchResultOnMapInFocusObserver()
	{
		m_nativeToUiMessageBus.Unsubscribe(m_gainedFocusHandler);
		m_nativeToUiMessageBus.Unsubscribe(m_lostFocusHandler);
		m_nativeToUiMessageBus.Unsubscribe(m_focusScreenLocationUpdatedHandler);
	}
};
}
}
