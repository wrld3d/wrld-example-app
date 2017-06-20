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
            bool m_isTag;
            bool m_isInterior;
            bool m_shouldZoomToBuildingsView;

        public:
            SearchMenuPerformedSearchMessage(const std::string& searchQuery, bool isTag, bool isInterior);
            SearchMenuPerformedSearchMessage(const std::string& searchQuery, bool isTag, bool isInterior, bool shouldZoomToBuildingsView);

            const std::string& SearchQuery() const;
            
            bool IsTag() const;
            
            bool IsInterior() const;

            bool ShouldZoomToBuildingsView() const;
        };
    }
}
