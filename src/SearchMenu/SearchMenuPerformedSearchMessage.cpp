// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuPerformedSearchMessage.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        SearchMenuPerformedSearchMessage::SearchMenuPerformedSearchMessage(const std::string& searchQuery, bool isTag, bool isInterior)
        : m_searchQuery(searchQuery)
        , m_isTag(isTag)
        , m_isInterior(isInterior)
        {
            
        }
        
        const std::string& SearchMenuPerformedSearchMessage::SearchQuery() const
        {
            return m_searchQuery;
        }
        
        bool SearchMenuPerformedSearchMessage::IsTag() const
        {
            return m_isTag;
        }
        
        bool SearchMenuPerformedSearchMessage::IsInterior() const
        {
            return m_isInterior;
        }
    }
}
