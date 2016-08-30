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
                std::shared_ptr<ISearchService> m_searchService;
                std::shared_ptr<ISearchQueryPerformer> m_searchQueryPerformer;
                std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                Eegeo::Helpers::TCallback1<SearchQueryObserver, const SearchQuery&> m_searchQueryPerformedCallback;
                Eegeo::Helpers::TCallback2<SearchQueryObserver, const SearchQuery&, const std::vector<SearchResultModel>&> m_searchQueryResponseCallback;
                Eegeo::Helpers::TCallback0<SearchQueryObserver> m_searchQueryResultsClearedCallback;

                void HandleSearchQueryPerformed(const SearchQuery& query);

                void HandleSearchQueryResponseReceived(const SearchQuery& query, const std::vector<SearchResultModel>& results);

                void HandleSearchQueryCleared();

            public:
                SearchQueryObserver(const std::shared_ptr<ISearchService>& searchService,
                                    const std::shared_ptr<ISearchQueryPerformer>& searchQueryPerformer,
                                    const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);

                ~SearchQueryObserver();
            };
        }
    }
}
