// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "SearchMenuSearchWithContextMessage.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        SearchMenuSearchWithContextMessage::SearchMenuSearchWithContextMessage(const std::string& searchQuery, bool isTag, bool isInterior,
                                                                               bool shouldZoomToBuildingsView,
                                                                               const Eegeo::Space::LatLongAltitude& location, float radius)
        : m_searchQuery(searchQuery)
        , m_isTag(isTag)
        , m_isInterior(isInterior)
        , m_shouldZoomToBuildingsView(shouldZoomToBuildingsView)
        , m_usesLocationAndRadius(true)
        , m_location(location)
        , m_radius(radius)
        {
            
        }

        SearchMenuSearchWithContextMessage::SearchMenuSearchWithContextMessage(const std::string& searchQuery, bool isTag, bool isInterior,
                                                                               bool shouldZoomToBuildingsView)
        : m_searchQuery(searchQuery)
        , m_isTag(isTag)
        , m_isInterior(isInterior)
        , m_shouldZoomToBuildingsView(shouldZoomToBuildingsView)
        , m_usesLocationAndRadius(false)
        , m_location(0, 0, 0)
        , m_radius(0)
        {

        }

        const std::string& SearchMenuSearchWithContextMessage::SearchQuery() const
        {
            return m_searchQuery;
        }

        bool SearchMenuSearchWithContextMessage::IsTag() const
        {
            return m_isTag;
        }

        bool SearchMenuSearchWithContextMessage::IsInterior() const
        {
            return m_isInterior;
        }

        bool SearchMenuSearchWithContextMessage::ShouldZoomToBuildingsView() const
        {
            return m_shouldZoomToBuildingsView;
        }

        bool SearchMenuSearchWithContextMessage::UsesLocationAndRadius() const
        {
            return m_usesLocationAndRadius;
        }

        const Eegeo::Space::LatLongAltitude& SearchMenuSearchWithContextMessage::Location() const
        {
            return m_location;
        }

        float SearchMenuSearchWithContextMessage::Radius() const
        {
            return m_radius;
        }
    }
}
