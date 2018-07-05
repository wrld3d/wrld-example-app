// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchQueryResponseReceivedMessage.h"

namespace ExampleApp
{
    namespace Search
    {
        SearchQueryResponseReceivedMessage::SearchQueryResponseReceivedMessage(const bool didSucceed,
                                                                               const SdkModel::SearchQuery& query,
                                                                               const std::vector<SdkModel::SearchResultModel>& results)
            : m_didSucceed(didSucceed)
            , m_query(query)
            , m_results(results)
        {
        }

        const bool SearchQueryResponseReceivedMessage::DidSucceed() const
        {
            return m_didSucceed;
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
