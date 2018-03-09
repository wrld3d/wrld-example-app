// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "LatLongAltitude.h"
#include <string>

namespace ExampleApp
{
    namespace SearchMenu
    {
        class SearchMenuRefreshedSearchMessage
        {
            std::string m_searchQuery;
            bool m_isTag;
            bool m_isInterior;
            bool m_shouldZoomToBuildingsView;
            Eegeo::Space::LatLongAltitude m_location;
            float m_radius;

        public:
            SearchMenuRefreshedSearchMessage(const std::string& searchQuery, bool isTag, bool isInterior,
                                             bool shouldZoomToBuildingsView,
                                             const Eegeo::Space::LatLongAltitude& location, float radius);

            const std::string& SearchQuery() const;
            bool IsTag() const;
            bool IsInterior() const;
            bool ShouldZoomToBuildingsView() const;
            const Eegeo::Space::LatLongAltitude& Location() const;
            float Radius() const;
        };
    }
}
