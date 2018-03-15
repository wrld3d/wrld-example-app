// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "QueryContext.h"

namespace ExampleApp
{
	namespace SearchMenu
	{
		namespace View
		{
			QueryContext::QueryContext(bool isTag,
									   const std::string& tagText,
									   bool shouldTryInterior,
									   bool shouldZoomToBuildingsView)
			: m_isTag(isTag)
			, m_tagText(tagText)
			, m_shouldTryInterior(shouldTryInterior)
			, m_shouldZoomToBuildingsView(shouldZoomToBuildingsView)
			, m_usesLocationAndRadius(false)
			, m_location(0, 0, 0)
			, m_radius(0)
			{
			}

			QueryContext::QueryContext(bool isTag,
									   const std::string& tagText,
									   bool shouldTryInterior,
									   bool shouldZoomToBuildingsView,
									   const Eegeo::Space::LatLongAltitude& location,
									   float radius)
			: m_isTag(isTag)
			, m_tagText(tagText)
			, m_shouldTryInterior(shouldTryInterior)
			, m_shouldZoomToBuildingsView(shouldZoomToBuildingsView)
			, m_usesLocationAndRadius(true)
			, m_location(location)
			, m_radius(radius)
			{
			}

			bool QueryContext::IsTag() const
			{
				return m_isTag;
			}

			const std::string& QueryContext::TagText() const
			{
				return m_tagText;
			}

			bool QueryContext::ShouldTryInterior() const
			{
				return m_shouldTryInterior;
			}

			bool QueryContext::ShouldZoomToBuildingsView() const
			{
				return m_shouldZoomToBuildingsView;
			}

			bool QueryContext::UsesLocationAndRadius() const
			{
				return m_usesLocationAndRadius;
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
