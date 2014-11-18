// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchQueryResponseReceivedMessage.h"

namespace ExampleApp
{
    namespace Search
    {
        SearchQueryResponseReceivedMessage::SearchQueryResponseReceivedMessage(const Search::SearchQuery& query,
                                                                               const std::vector<SearchResultModel>& results)
        : m_query(query)
        , m_results(results)
        {
        }
        
        const Search::SearchQuery SearchQueryResponseReceivedMessage::GetQuery() const
        {
            return m_query;
        }
        const std::vector<SearchResultModel>& SearchQueryResponseReceivedMessage::GetResults() const
        {
            return m_results;
        }
    }
}
