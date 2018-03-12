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
				bool m_shouldZoomToBuildingsView;
				bool m_usesLocationAndRadius;
				Eegeo::Space::LatLongAltitude m_location;
				float m_radius;

			public:
				QueryContext(bool isTag, bool shouldTryInterior, bool shouldZoomToBuildingsView);

				QueryContext(bool isTag, bool shouldTryInterior, bool shouldZoomToBuildingsView,
							 const Eegeo::Space::LatLongAltitude& location,
							 float radius);

				bool IsTag() const;
				bool ShouldTryInterior() const;
				bool ShouldZoomToBuildingsView() const;
				bool UsesLocationAndRadius() const;
				const Eegeo::Space::LatLongAltitude& Location() const;
				float Radius() const;
			};
		}
	}
}
