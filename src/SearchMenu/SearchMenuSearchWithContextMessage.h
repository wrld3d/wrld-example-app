// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "QueryContext.h"
#include <string>

namespace ExampleApp
{
    namespace SearchMenu
    {
        class SearchMenuSearchWithContextMessage
        {
            std::string m_searchQuery;
            View::QueryContext m_queryContext;

        public:
            SearchMenuSearchWithContextMessage(const std::string& searchQuery,
                                               const View::QueryContext& context);

            const std::string& SearchQuery() const;
            const View::QueryContext& QueryContext() const;
        };
    }
}
