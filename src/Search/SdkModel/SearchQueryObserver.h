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

			void HandleSearchQueryPerformed(const Search::SearchQuery& query);

			void HandleSearchQueryResponseReceived(const Search::SearchQuery& query, const std::vector<SearchResultModel>& results);

			void HandleSearchQueryCleared();

		public:
			SearchQueryObserver(ISearchService& searchService,
			                    ISearchQueryPerformer& searchQueryPerformer,
			                    ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);

			~SearchQueryObserver();
		};
	}
}
