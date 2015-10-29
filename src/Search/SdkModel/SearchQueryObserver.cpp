// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchQueryObserver.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            SearchQueryObserver::SearchQueryObserver(ISearchService& exteriorSearchService,
                                                     ISearchService& interiorSearchService,
                    ISearchQueryPerformer& searchQueryPerformer,
                    ExampleAppMessaging::TMessageBus& messageBus)
                : m_exteriorSearchService(exteriorSearchService)
                , m_interiorSearchService(interiorSearchService)
                , m_searchQueryPerformer(searchQueryPerformer)
                , m_messageBus(messageBus)
                , m_searchQueryPerformedCallback(this, &SearchQueryObserver::HandleSearchQueryPerformed)
                , m_searchQueryResponseCallback(this, &SearchQueryObserver::HandleSearchQueryResponseReceived)
                , m_searchQueryResultsClearedCallback(this, &SearchQueryObserver::HandleSearchQueryCleared)
            {
                m_exteriorSearchService.InsertOnPerformedQueryCallback(m_searchQueryPerformedCallback);
                m_exteriorSearchService.InsertOnReceivedQueryResultsCallback(m_searchQueryResponseCallback);
                
                m_interiorSearchService.InsertOnPerformedQueryCallback(m_searchQueryPerformedCallback);
                m_interiorSearchService.InsertOnReceivedQueryResultsCallback(m_searchQueryResponseCallback);
                m_searchQueryPerformer.InsertOnSearchResultsClearedCallback(m_searchQueryResultsClearedCallback);
            }

            SearchQueryObserver::~SearchQueryObserver()
            {
                m_exteriorSearchService.RemoveOnPerformedQueryCallback(m_searchQueryPerformedCallback);
                m_exteriorSearchService.RemoveOnReceivedQueryResultsCallback(m_searchQueryResponseCallback);
                
                m_interiorSearchService.RemoveOnPerformedQueryCallback(m_searchQueryPerformedCallback);
                m_interiorSearchService.RemoveOnReceivedQueryResultsCallback(m_searchQueryResponseCallback);
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
