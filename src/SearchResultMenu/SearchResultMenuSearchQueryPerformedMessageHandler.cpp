// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultMenuSearchQueryPerformedMessageHandler.h"

namespace ExampleApp
{
	namespace SearchResultMenu
	{
		SearchResultMenuSearchQueryPerformedMessageHandler::SearchResultMenuSearchQueryPerformedMessageHandler(
			SearchResultMenu::ISearchResultMenuViewModel& searchResultMenuViewModel,
			ExampleAppMessaging::NativeToUiMessageBus& messageBus)
			: m_searchResultMenuViewModel(searchResultMenuViewModel)
			, m_messageBus(messageBus)
			, m_handlerBinding(this, &SearchResultMenuSearchQueryPerformedMessageHandler::HandleReceivedSearchQueryPerformedMessage)
		{
			m_messageBus.Subscribe(m_handlerBinding);
		}

		SearchResultMenuSearchQueryPerformedMessageHandler::~SearchResultMenuSearchQueryPerformedMessageHandler()
		{
			m_messageBus.Unsubscribe(m_handlerBinding);
		}

		void SearchResultMenuSearchQueryPerformedMessageHandler::HandleReceivedSearchQueryPerformedMessage(const Search::SearchQueryPerformedMessage& message)
		{
			m_searchResultMenuViewModel.SetHasSearchQuery(true);
		}
	}
}
