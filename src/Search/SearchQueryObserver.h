// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "ISearchService.h"
#include "ISearchQueryPerformer.h"
#include "ICallback.h"
#include "NativeToUiMessageBus.h"
#include "SearchQueryPerformedMessage.h"
#include "SearchQueryRemovedMessage.h"
#include "SearchQueryResponseReceivedMessage.h"

namespace ExampleApp
{
	namespace Search
	{
		class SearchQueryObserver : private Eegeo::NonCopyable
		{
			ISearchService& m_searchService;
			ISearchQueryPerformer& m_searchQueryPerformer;
			ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;
			Eegeo::Helpers::TCallback1<SearchQueryObserver, const Search::SearchQuery&> m_searchQueryPerformedCallback;
			Eegeo::Helpers::TCallback2<SearchQueryObserver, const Search::SearchQuery&, const std::vector<SearchResultModel>&> m_searchQueryResponseCallback;
			Eegeo::Helpers::TCallback0<SearchQueryObserver> m_searchQueryResultsClearedCallback;

			void HandleSearchQueryPerformed(const Search::SearchQuery& query)
			{
				m_nativeToUiMessageBus.Publish(SearchQueryPerformedMessage(query));
			}

			void HandleSearchQueryResponseReceived(const Search::SearchQuery& query, const std::vector<SearchResultModel>& results)
			{
				m_nativeToUiMessageBus.Publish(SearchQueryResponseReceivedMessage(query, results));
			}

			void HandleSearchQueryCleared()
			{
				m_nativeToUiMessageBus.Publish(SearchQueryRemovedMessage());
			}

		public:
			SearchQueryObserver(ISearchService& searchService,
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

			~SearchQueryObserver()
			{
				m_searchService.RemoveOnPerformedQueryCallback(m_searchQueryPerformedCallback);
				m_searchService.RemoveOnReceivedQueryResultsCallback(m_searchQueryResponseCallback);
				m_searchQueryPerformer.RemoveOnSearchResultsClearedCallback(m_searchQueryResultsClearedCallback);
			}
		};
	}
}
