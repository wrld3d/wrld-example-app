// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "DeepLinkedSearchQueryRequestMessage.h"

namespace ExampleApp
{
    namespace Search
    {
        DeepLinkedSearchQueryRequestMessage::DeepLinkedSearchQueryRequestMessage(const SdkModel::SearchQuery& searchQuery)
        : m_query(searchQuery)
        {
        }
        
        const SdkModel::SearchQuery& DeepLinkedSearchQueryRequestMessage::Query() const
        {
            return m_query;
        }
    }
}
