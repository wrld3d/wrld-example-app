// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "QueryContext.h"

namespace ExampleApp
{
	namespace SearchMenu
	{
		namespace View
		{
			QueryContext::QueryContext(bool isTag,
									   bool shouldTryInterior,
									   bool shouldZoomToBuildingsView,
									   const Eegeo::Space::LatLongAltitude& location,
									   float radius)
			: m_isTag(isTag)
			, m_shouldTryInterior(shouldTryInterior)
			, m_shouldZoomToBuildingsView(shouldZoomToBuildingsView)
			, m_location(location)
			, m_radius(radius)
			{
			}

			bool QueryContext::IsTag() const
			{
				return m_isTag;
			}

			bool QueryContext::ShouldTryInterior() const
			{
				return m_shouldTryInterior;
			}

			bool QueryContext::ShouldZoomToBuildingsView() const
			{
				return m_shouldZoomToBuildingsView;
			}

			const Eegeo::Space::LatLongAltitude& QueryContext::Location() const
			{
				return m_location;
			}

			float QueryContext::Radius() const
			{
				return m_radius;
			}
		}
	}
}
