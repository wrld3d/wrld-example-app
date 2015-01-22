// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchQueryPerformedMessage.h"

namespace ExampleApp
{
    namespace Search
    {
        SearchQueryPerformedMessage::SearchQueryPerformedMessage(const SdkModel::SearchQuery& searchQuery)
            : m_query(searchQuery)
        {

        }

        const SdkModel::SearchQuery& SearchQueryPerformedMessage::Query() const
        {
            return m_query;
        }
    }
}
