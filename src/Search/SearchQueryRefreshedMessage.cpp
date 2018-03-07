// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "SearchQueryRefreshedMessage.h"

namespace ExampleApp
{
    namespace Search
    {
        SearchQueryRefreshedMessage::SearchQueryRefreshedMessage(const SdkModel::SearchQuery& searchQuery,
                                                                 bool useRadius)
        : m_query(searchQuery)
        , m_useRadius(useRadius)
        {
        }

        const SdkModel::SearchQuery& SearchQueryRefreshedMessage::Query() const
        {
            return m_query;
        }

        bool SearchQueryRefreshedMessage::UseRadius() const
        {
            return m_useRadius;
        }
    }
}
