// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "SearchQuery.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace Search
    {
        class SearchQueryRefreshedMessage
        {
            SdkModel::SearchQuery m_query;
			bool m_shouldZoomToBuildingsView;
			Eegeo::Space::LatLongAltitude m_location;
            float m_radius;

        public:
			SearchQueryRefreshedMessage(const SdkModel::SearchQuery& searchQuery,
										bool shouldZoomToBuildingsView,
										const Eegeo::Space::LatLongAltitude& location,
										float radius);

            const SdkModel::SearchQuery& Query() const;
			bool ShouldZoomToBuildingsView() const;
			const Eegeo::Space::LatLongAltitude& Location() const;
			float Radius() const;
        };
    }
}
