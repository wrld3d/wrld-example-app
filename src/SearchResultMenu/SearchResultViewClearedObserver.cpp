//  Copyright (c) 2014 eeGeo. All rights reserved.

#include "SearchResultViewClearedObserver.h"

namespace ExampleApp
{
	namespace SearchResultMenu
	{
		SearchResultViewClearedObserver::SearchResultViewClearedObserver(Search::ISearchQueryPerformer& searchQueryPerformer,
										ExampleApp::ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
			: m_searchQueryPerformer(searchQueryPerformer)
			, m_uiToNativeMessageBus(uiToNativeMessageBus)
			, m_handler(this, &SearchResultViewClearedObserver::OnSearchResultViewCleared)
		{
			m_uiToNativeMessageBus.Subscribe(m_handler);
		}

		SearchResultViewClearedObserver::~SearchResultViewClearedObserver()
		{
			m_uiToNativeMessageBus.Unsubscribe(m_handler);
		}
		void SearchResultViewClearedObserver::OnSearchResultViewCleared(const SearchResultViewClearedMessage& message)
		{
			m_searchQueryPerformer.RemoveSearchQueryResults();
		}
	}
}
