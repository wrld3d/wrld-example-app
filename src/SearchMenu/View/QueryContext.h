// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "LatLongAltitude.h"

#include <string>

namespace ExampleApp
{
    namespace SearchMenu
    {
		namespace View
		{
			class QueryContext
			{
				bool m_clearPreviousResults;
				bool m_isTag;
				std::string m_tagText;
				bool m_shouldTryInterior;
				bool m_usesLocation;
				Eegeo::Space::LatLongAltitude m_location;
				bool m_usesRadius;
				float m_radius;

			public:
				QueryContext(bool clearPreviousResults,
							 bool isTag, const std::string& tagText,
							 bool shouldTryInterior);

				QueryContext(bool clearPreviousResults,
							 bool isTag, const std::string& tagText,
							 bool shouldTryInterior,
							 float radius);

				QueryContext(bool clearPreviousResults,
							 bool isTag, const std::string& tagText,
							 bool shouldTryInterior,
							 const Eegeo::Space::LatLongAltitude& location,
							 float radius);

				bool ClearPreviousResults() const;
				bool IsTag() const;
				const std::string& TagText() const;
				bool ShouldTryInterior() const;
				bool UsesLocation() const;
				const Eegeo::Space::LatLongAltitude& Location() const;
				bool UsesRadius() const;
				float Radius() const;
			};
		}
	}
}
