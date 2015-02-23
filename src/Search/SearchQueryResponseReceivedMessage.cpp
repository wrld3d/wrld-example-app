// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchQueryResponseReceivedMessage.h"

namespace ExampleApp
{
    namespace Search
    {
        SearchQueryResponseReceivedMessage::SearchQueryResponseReceivedMessage(const SdkModel::SearchQuery& query,
                const std::vector<SdkModel::SearchResultModel>& results)
            : m_query(query)
            , m_results(results)
        {
        }

        const SdkModel::SearchQuery SearchQueryResponseReceivedMessage::GetQuery() const
        {
            return m_query;
        }
        const std::vector<SdkModel::SearchResultModel>& SearchQueryResponseReceivedMessage::GetResults() const
        {
            return m_results;
        }
    }
}
