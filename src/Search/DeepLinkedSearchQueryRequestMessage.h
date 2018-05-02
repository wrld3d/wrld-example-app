// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "SearchQuery.h"

namespace ExampleApp
{
    namespace Search
    {
        class DeepLinkedSearchQueryRequestMessage
        {
            SdkModel::SearchQuery m_query;
            
        public:
            DeepLinkedSearchQueryRequestMessage(const SdkModel::SearchQuery& searchQuery);
            
            const SdkModel::SearchQuery& Query() const;
        };
    }
}
