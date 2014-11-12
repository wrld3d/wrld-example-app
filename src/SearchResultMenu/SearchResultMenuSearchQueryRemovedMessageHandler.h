// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "NativeToUiMessageBus.h"
#include "ICallback.h"
#include "SearchQueryRemovedMessage.h"
#include "ISearchResultMenuViewModel.h"

namespace ExampleApp
{
	namespace SearchResultMenu
	{
		class SearchResultMenuSearchQueryRemovedMessageHandler : private Eegeo::NonCopyable
		{
			SearchResultMenu::ISearchResultMenuViewModel& m_searchResultMenuViewModel;
			ExampleAppMessaging::NativeToUiMessageBus& m_messageBus;
			Eegeo::Helpers::TCallback1<SearchResultMenuSearchQueryRemovedMessageHandler, const Search::SearchQueryRemovedMessage&> m_handlerBinding;

			void HandleReceivedSearchQueryRemovedMessage(const Search::SearchQueryRemovedMessage& message)
			{
				m_searchResultMenuViewModel.SetHasSearchQuery(false);
			}

		public:
			SearchResultMenuSearchQueryRemovedMessageHandler(
			    SearchResultMenu::ISearchResultMenuViewModel& searchResultMenuViewModel,
			    ExampleAppMessaging::NativeToUiMessageBus& messageBus)
				: m_searchResultMenuViewModel(searchResultMenuViewModel)
				, m_messageBus(messageBus)
				, m_handlerBinding(this, &SearchResultMenuSearchQueryRemovedMessageHandler::HandleReceivedSearchQueryRemovedMessage)
			{
				m_messageBus.Subscribe(m_handlerBinding);
			}

			~SearchResultMenuSearchQueryRemovedMessageHandler()
			{
				m_messageBus.Unsubscribe(m_handlerBinding);
			}
		};
	}
}
