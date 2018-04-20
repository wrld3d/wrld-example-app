// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "SearchMenuSearchWithContextMessage.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        SearchMenuSearchWithContextMessage::SearchMenuSearchWithContextMessage(const std::string& searchQuery,
                                                                               const View::QueryContext& queryContext)
        : m_searchQuery(searchQuery)
        , m_queryContext(queryContext)
                {
        }

        const std::string& SearchMenuSearchWithContextMessage::SearchQuery() const
        {
            return m_searchQuery;
        }

        const View::QueryContext& SearchMenuSearchWithContextMessage::QueryContext() const
        {
            return m_queryContext;
        }
    }
}
