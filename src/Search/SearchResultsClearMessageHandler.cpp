// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultsClearMessageHandler.h"
#include "ISearchQueryPerformer.h"

namespace ExampleApp
{
	namespace Search
	{
		SearchResultsClearMessageHandler::SearchResultsClearMessageHandler(
			ISearchQueryPerformer& searchQueryPerformer,
			ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
		: m_searchQueryPerformer(searchQueryPerformer)
		, m_uiToNativeMessageBus(uiToNativeMessageBus)
		, m_handlerBinding(this, &SearchResultsClearMessageHandler::HandleReceivedSearchResultsClearMessage)
		{
			m_uiToNativeMessageBus.Subscribe(m_handlerBinding);
		}

		SearchResultsClearMessageHandler::~SearchResultsClearMessageHandler()
		{
			m_uiToNativeMessageBus.Unsubscribe(m_handlerBinding);
		}

		void SearchResultsClearMessageHandler::HandleReceivedSearchResultsClearMessage(const SearchResultsClearMessage& message)
		{
			m_searchQueryPerformer.RemoveSearchQueryResults();
		}
	}
}
