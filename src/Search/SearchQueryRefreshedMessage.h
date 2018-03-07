// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "SearchQuery.h"

namespace ExampleApp
{
    namespace Search
    {
        class SearchQueryRefreshedMessage
        {
            SdkModel::SearchQuery m_query;
            bool m_useRadius;

        public:
            SearchQueryRefreshedMessage(const SdkModel::SearchQuery& searchQuery, bool useRadius);

            const SdkModel::SearchQuery& Query() const;
            bool UseRadius() const;
        };
    }
}
