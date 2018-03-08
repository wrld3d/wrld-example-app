// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "SearchQueryRefreshedMessage.h"

namespace ExampleApp
{
    namespace Search
    {
		SearchQueryRefreshedMessage::SearchQueryRefreshedMessage(const SdkModel::SearchQuery& searchQuery,
																 bool shouldZoomToBuildingsView,
																 const Eegeo::Space::LatLongAltitude& location,
																 float radius)
		: m_query(searchQuery)
		, m_shouldZoomToBuildingsView(shouldZoomToBuildingsView)
		, m_location(location)
		, m_radius(radius)
		{
		}

		const SdkModel::SearchQuery& SearchQueryRefreshedMessage::Query() const
        {
            return m_query;
        }

		bool SearchQueryRefreshedMessage::ShouldZoomToBuildingsView() const
		{
			return m_shouldZoomToBuildingsView;
		}

		const Eegeo::Space::LatLongAltitude& SearchQueryRefreshedMessage::Location() const
		{
			return m_location;
		}

		float SearchQueryRefreshedMessage::Radius() const
		{
			return m_radius;
		}
    }
}
