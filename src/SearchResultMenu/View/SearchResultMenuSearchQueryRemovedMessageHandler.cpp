// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultMenuSearchQueryRemovedMessageHandler.h"

namespace ExampleApp
{
	namespace SearchResultMenu
	{
		SearchResultMenuSearchQueryRemovedMessageHandler::SearchResultMenuSearchQueryRemovedMessageHandler(
			SearchResultMenu::ISearchResultMenuViewModel& searchResultMenuViewModel,
			ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
			: m_searchResultMenuViewModel(searchResultMenuViewModel)
			, m_nativeToUiMessageBus(nativeToUiMessageBus)
			, m_handlerBinding(this, &SearchResultMenuSearchQueryRemovedMessageHandler::HandleReceivedSearchQueryRemovedMessage)
		{
			m_nativeToUiMessageBus.Subscribe(m_handlerBinding);
		}

		SearchResultMenuSearchQueryRemovedMessageHandler::~SearchResultMenuSearchQueryRemovedMessageHandler()
		{
			m_nativeToUiMessageBus.Unsubscribe(m_handlerBinding);
		}

		void SearchResultMenuSearchQueryRemovedMessageHandler::HandleReceivedSearchQueryRemovedMessage(const Search::SearchQueryRemovedMessage& message)
		{
			m_searchResultMenuViewModel.SetHasSearchQuery(false);
		}
	}
}
