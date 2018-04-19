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
			Eegeo::Space::LatLongAltitude m_location;
            float m_radius;

        public:
			SearchQueryRefreshedMessage(const SdkModel::SearchQuery& searchQuery,
										const Eegeo::Space::LatLongAltitude& location,
										float radius);

            const SdkModel::SearchQuery& Query() const;
			const Eegeo::Space::LatLongAltitude& Location() const;
			float Radius() const;
        };
    }
}
