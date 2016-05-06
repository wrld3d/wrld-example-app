// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ISearchService.h"
#include "Search.h"
#include "ICallback.h"
#include "BidirectionalBus.h"
#include "SearchQueryPerformedMessage.h"
#include "SearchQueryRemovedMessage.h"
#include "SearchQueryResponseReceivedMessage.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            class SearchQueryObserver : private Eegeo::NonCopyable
            {
                ISearchService& m_searchService;
                ISearchQueryPerformer& m_searchQueryPerformer;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<SearchQueryObserver, const SearchQuery&> m_searchQueryPerformedCallback;
                Eegeo::Helpers::TCallback2<SearchQueryObserver, const SearchQuery&, const std::vector<SearchResultModel>&> m_searchQueryResponseCallback;
                Eegeo::Helpers::TCallback0<SearchQueryObserver> m_searchQueryResultsClearedCallback;

                void HandleSearchQueryPerformed(const SearchQuery& query);

                void HandleSearchQueryResponseReceived(const SearchQuery& query, const std::vector<SearchResultModel>& results);

                void HandleSearchQueryCleared();

            public:
                SearchQueryObserver(ISearchService& searchService,
                                    ISearchQueryPerformer& searchQueryPerformer,
                                    ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchQueryObserver();
            };
        }
    }
}
