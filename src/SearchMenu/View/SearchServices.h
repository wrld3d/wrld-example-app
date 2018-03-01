// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "ISearchProvider.h"
#include "BidirectionalBus.h"
#include "CallbackCollection.h"
#include "SearchQueryResponseReceivedMessage.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
		namespace View
		{
			class SearchServices: private Eegeo::NonCopyable
			{
			private:
				ISearchProvider& m_searchProvider;
				ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback1<SearchServices, const std::string&> m_onSearchCallback;
				Eegeo::Helpers::TCallback1<SearchServices, const Search::SearchQueryResponseReceivedMessage&> m_responseReceivedHandler;

				ISearchProvider::TSearchResults m_searchResults;

			public:
				SearchServices(ISearchProvider& searchProvider,
							   ExampleAppMessaging::TMessageBus& messageBus);
				~SearchServices();

			private:
				void OnSearch(const std::string& searchQuery);
				void OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message);
			};
		}
	}
}
