// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuPerformedSearchMessage.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        SearchMenuPerformedSearchMessage::SearchMenuPerformedSearchMessage(const std::string& searchQuery, bool isCategory, bool isInterior)
        : m_searchQuery(searchQuery)
        , m_isCategory(isCategory)
        , m_isInterior(isInterior)
        {
            
        }
        
        const std::string& SearchMenuPerformedSearchMessage::SearchQuery() const
        {
            return m_searchQuery;
        }
        
        bool SearchMenuPerformedSearchMessage::IsCategory() const
        {
            return m_isCategory;
        }
        
        bool SearchMenuPerformedSearchMessage::IsInterior() const
        {
            return m_isInterior;
        }
    }
}
