// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "QueryContext.h"

namespace ExampleApp
{
	namespace SearchMenu
	{
		namespace View
		{
			QueryContext::QueryContext(bool clearPreviousResults,
									   bool isTag,
									   const std::string& tagText,
									   bool shouldTryInterior)
			: m_clearPreviousResults(clearPreviousResults)
			, m_isTag(isTag)
			, m_tagText(tagText)
			, m_shouldTryInterior(shouldTryInterior)
			, m_usesLocation(false)
			, m_location(0, 0, 0)
			, m_usesRadius(false)
			, m_radius(0)
			{
			}

			QueryContext::QueryContext(bool clearPreviousResults,
									   bool isTag,
									   const std::string& tagText,
									   bool shouldTryInterior,
									   float radius)
			: m_clearPreviousResults(clearPreviousResults)
			, m_isTag(isTag)
			, m_tagText(tagText)
			, m_shouldTryInterior(shouldTryInterior)
			, m_usesLocation(false)
			, m_location(0, 0, 0)
			, m_usesRadius(true)
			, m_radius(radius)
			{
			}

			QueryContext::QueryContext(bool clearPreviousResults,
									   bool isTag,
									   const std::string& tagText,
									   bool shouldTryInterior,
									   const Eegeo::Space::LatLongAltitude& location,
									   float radius)
			: m_clearPreviousResults(clearPreviousResults)
			, m_isTag(isTag)
			, m_tagText(tagText)
			, m_shouldTryInterior(shouldTryInterior)
			, m_usesLocation(true)
			, m_location(location)
			, m_usesRadius(true)
			, m_radius(radius)
			{
			}

			bool QueryContext::ClearPreviousResults() const
			{
				return m_clearPreviousResults;
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

			bool QueryContext::UsesLocation() const
			{
				return m_usesLocation;
			}

			const Eegeo::Space::LatLongAltitude& QueryContext::Location() const
			{
				return m_location;
			}

			bool QueryContext::UsesRadius() const
			{
				return m_usesRadius;
			}

			float QueryContext::Radius() const
			{
				return m_radius;
			}
		}
	}
}
