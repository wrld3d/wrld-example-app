// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchQuery.h"

namespace ExampleApp
{
    namespace Search
    {
        class SearchQueryPerformedMessage
        {
            SdkModel::SearchQuery m_query;

        public:
            SearchQueryPerformedMessage(const SdkModel::SearchQuery& searchQuery);

            const SdkModel::SearchQuery& Query() const;
        };
    }
}
