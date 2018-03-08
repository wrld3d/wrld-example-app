// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "QueryContext.h"

namespace ExampleApp
{
	namespace SearchMenu
	{
		namespace View
		{
			QueryContext::QueryContext(bool isTag, bool shouldTryInterior,
															 const Eegeo::Space::LatLongAltitude& location,
															 float radius)
			: m_isTag(isTag)
			, m_shouldTryInterior(shouldTryInterior)
			, m_location(location)
			, m_radius(radius)
			{
			}

			bool QueryContext::GetIsTag() const
			{
				return m_isTag;
			}
			bool QueryContext::GetShouldTryInterior() const
			{
				return m_shouldTryInterior;
			}
			const Eegeo::Space::LatLongAltitude& QueryContext::GetLocation() const
			{
				return m_location;
			}
			float QueryContext::GetRadius() const
			{
				return m_radius;
			}
		}
	}
}
