// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "SearchQuery.h"

namespace ExampleApp
{
    namespace Search
    {
        class SearchQueryRequestMessage
        {
            SdkModel::SearchQuery m_query;
            
        public:
            SearchQueryRequestMessage(const SdkModel::SearchQuery& searchQuery);
            
            const SdkModel::SearchQuery& Query() const;
        };
    }
}
