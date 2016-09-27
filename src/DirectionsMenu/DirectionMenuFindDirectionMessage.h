// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        class DirectionMenuFindDirectionMessage
        {
            std::string m_searchQuery;
            bool m_isInterior;
            
        public:
            
            DirectionMenuFindDirectionMessage(const std::string& searchQuery, bool isInterior);
            const std::string& SearchQuery() const;
            bool IsInterior() const;
        };
    }
}