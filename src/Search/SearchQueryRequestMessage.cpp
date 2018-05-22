// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "SearchQueryRequestMessage.h"

namespace ExampleApp
{
    namespace Search
    {
        SearchQueryRequestMessage::SearchQueryRequestMessage(const SdkModel::SearchQuery& searchQuery)
        : m_query(searchQuery)
        {
        }
        
        const SdkModel::SearchQuery& SearchQueryRequestMessage::Query() const
        {
            return m_query;
        }
    }
}
