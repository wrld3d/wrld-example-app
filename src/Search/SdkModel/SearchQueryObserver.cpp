// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchQueryObserver.h"
#include "ISearchQueryPerformer.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            SearchQueryObserver::SearchQueryObserver(ISearchService& searchService,
                    ISearchQueryPerformer& searchQueryPerformer,
                    ExampleAppMessaging::TMessageBus& messageBus)
                : m_searchService(searchService)
                , m_searchQueryPerformer(searchQueryPerformer)
                , m_messageBus(messageBus)
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

            void SearchQueryObserver::HandleSearchQueryPerformed(const SearchQuery& query)
            {
                m_messageBus.Publish(SearchQueryPerformedMessage(query));
            }

            void SearchQueryObserver::HandleSearchQueryResponseReceived(const SearchQuery& query, const std::vector<SearchResultModel>& results)
            {
                m_messageBus.Publish(SearchQueryResponseReceivedMessage(query, results));
            }

            void SearchQueryObserver::HandleSearchQueryCleared()
            {
                m_messageBus.Publish(SearchQueryRemovedMessage());
            }
        }
    }
}
