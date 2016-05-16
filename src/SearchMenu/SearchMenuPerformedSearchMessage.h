// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace SearchMenu
    {
        class SearchMenuPerformedSearchMessage
        {
            std::string m_searchQuery;
            bool m_isCategory;
            bool m_isInterior;

        public:
            SearchMenuPerformedSearchMessage(const std::string& searchQuery, bool isCategory, bool isInterior);

            const std::string& SearchQuery() const;
            
            bool IsCategory() const;
            
            bool IsInterior() const;
        };
    }
}
