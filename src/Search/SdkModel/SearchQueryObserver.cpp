// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchQueryObserver.h"

namespace ExampleApp
{
	namespace Search
	{
		SearchQueryObserver::SearchQueryObserver(ISearchService& searchService,
							ISearchQueryPerformer& searchQueryPerformer,
							ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
			: m_searchService(searchService)
			, m_searchQueryPerformer(searchQueryPerformer)
			, m_nativeToUiMessageBus(nativeToUiMessageBus)
			, m_searchQueryPerformedCallback(this, &SearchQueryObserver::HandleSearchQueryPerformed)
			, m_searchQueryResponseCallback(this, &SearchQueryObserver::HandleSearchQueryResponseReceived)
			, m_searchQueryResultsClearedCallback(this, &SearchQueryObserver::HandleSearchQueryCleared)
		{
			m_searchService.InsertOnPerformedQueryCallback(m_searchQueryPerformedCallback);
			m_searchService.InsertOnReceivedQueryResultsCallback(m_searchQueryResponseCallback);
			m_searchQueryPerformer.InsertOnSearchResultsClearedCallback(m_searchQueryResultsClearedCallback);
		}

		SearchQueryObserver::~SearchQueryObserver()
		{
			m_searchService.RemoveOnPerformedQueryCallback(m_searchQueryPerformedCallback);
			m_searchService.RemoveOnReceivedQueryResultsCallback(m_searchQueryResponseCallback);
			m_searchQueryPerformer.RemoveOnSearchResultsClearedCallback(m_searchQueryResultsClearedCallback);
		}

		void SearchQueryObserver::HandleSearchQueryPerformed(const Search::SearchQuery& query)
		{
			m_nativeToUiMessageBus.Publish(SearchQueryPerformedMessage(query));
		}

		void SearchQueryObserver::HandleSearchQueryResponseReceived(const Search::SearchQuery& query, const std::vector<SearchResultModel>& results)
		{
			m_nativeToUiMessageBus.Publish(SearchQueryResponseReceivedMessage(query, results));
		}

		void SearchQueryObserver::HandleSearchQueryCleared()
		{
			m_nativeToUiMessageBus.Publish(SearchQueryRemovedMessage());
		}
	}
}
