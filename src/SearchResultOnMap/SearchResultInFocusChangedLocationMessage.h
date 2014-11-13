// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "VectorMath.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		class SearchResultInFocusChangedLocationMessage
		{
			Eegeo::v2 m_screenLocation;

		public:
			SearchResultInFocusChangedLocationMessage(const Eegeo::v2& screenLocation);

			const Eegeo::v2& ScreenLocation() const;
		};
	}
}
