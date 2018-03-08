// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
		namespace View
		{
			class QueryContext
			{
				bool m_isTag;
				bool m_shouldTryInterior;
				const Eegeo::Space::LatLongAltitude m_location;
				float m_radius;

			public:
				QueryContext(bool isTag, bool shouldTryInterior,
							 const Eegeo::Space::LatLongAltitude& location,
							 float radius);

				bool GetIsTag() const;
				bool GetShouldTryInterior() const;
				const Eegeo::Space::LatLongAltitude& GetLocation() const;
				float GetRadius() const;
			};
		}
	}
}
