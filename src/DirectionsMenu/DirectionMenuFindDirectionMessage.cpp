// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionMenuFindDirectionMessage.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        DirectionMenuFindDirectionMessage::DirectionMenuFindDirectionMessage(const std::string& searchQuery, bool isInterior)
        : m_searchQuery(searchQuery)
        , m_isInterior(isInterior)
        {
            
        }
        
        const std::string& DirectionMenuFindDirectionMessage::SearchQuery() const
        {
            return m_searchQuery;
        }
        
        bool DirectionMenuFindDirectionMessage::IsInterior() const
        {
            return m_isInterior;
        }
    }
}
