// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultOnMapInFocusObserver.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        SearchResultOnMapInFocusObserver::SearchResultOnMapInFocusObserver(
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
        
        SearchResultOnMapInFocusObserver::~SearchResultOnMapInFocusObserver()
        {
            m_nativeToUiMessageBus.Unsubscribe(m_gainedFocusHandler);
            m_nativeToUiMessageBus.Unsubscribe(m_lostFocusHandler);
            m_nativeToUiMessageBus.Unsubscribe(m_focusScreenLocationUpdatedHandler);
        }
        
        void SearchResultOnMapInFocusObserver::HandleReceivedSearchResultGainedFocusMessage(const SearchResultGainedFocusMessage& message)
        {
            m_searchResultOnMapInFocusViewModel.Open(message.FocussedModel(), message.ScreenLocation());
        }
        
        void SearchResultOnMapInFocusObserver::HandleReceivedSearchResultLostFocusMessage(const SearchResultLostFocusMessage& message)
        {
            m_searchResultOnMapInFocusViewModel.Close();
        }
        
        void  SearchResultOnMapInFocusObserver::HandleReceivedSearchResultInFocusChangedLocationMessage(const SearchResultInFocusChangedLocationMessage& message)
        {
            m_searchResultOnMapInFocusViewModel.UpdateScreenLocation(message.ScreenLocation());
        }
    }
}
