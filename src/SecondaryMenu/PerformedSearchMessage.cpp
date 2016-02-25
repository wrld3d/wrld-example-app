// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PerformedSearchMessage.h"

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        PerformedSearchMessage::PerformedSearchMessage(const std::string& searchQuery, bool isCategory, bool isInterior)
            : m_searchQuery(searchQuery)
            , m_isCategory(isCategory)
            , m_isInterior(isInterior)
        {

        }

        const std::string& PerformedSearchMessage::SearchQuery() const
        {
            return m_searchQuery;
        }

        bool PerformedSearchMessage::IsCategory() const
        {
            return m_isCategory;
        }
        
        bool PerformedSearchMessage::IsInterior() const
        {
            return m_isInterior;
        }
    }
}
