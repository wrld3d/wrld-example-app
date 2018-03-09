// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "SearchMenuRefreshedSearchMessage.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        SearchMenuRefreshedSearchMessage::SearchMenuRefreshedSearchMessage(const std::string& searchQuery, bool isTag, bool isInterior,
                                                                           bool shouldZoomToBuildingsView,
                                                                           const Eegeo::Space::LatLongAltitude& location, float radius)
        : m_searchQuery(searchQuery)
        , m_isTag(isTag)
        , m_isInterior(isInterior)
        , m_shouldZoomToBuildingsView(shouldZoomToBuildingsView)
        , m_location(location)
        , m_radius(radius)
        {
            
        }

        const std::string& SearchMenuRefreshedSearchMessage::SearchQuery() const
        {
            return m_searchQuery;
        }

        bool SearchMenuRefreshedSearchMessage::IsTag() const
        {
            return m_isTag;
        }

        bool SearchMenuRefreshedSearchMessage::IsInterior() const
        {
            return m_isInterior;
        }

        bool SearchMenuRefreshedSearchMessage::ShouldZoomToBuildingsView() const
        {
            return m_shouldZoomToBuildingsView;
        }

        const Eegeo::Space::LatLongAltitude& SearchMenuRefreshedSearchMessage::Location() const
        {
            return m_location;
        }

        float SearchMenuRefreshedSearchMessage::Radius() const
        {
            return m_radius;
        }
    }
}
