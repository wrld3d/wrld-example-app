// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultInFocusChangedLocationMessage.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		SearchResultInFocusChangedLocationMessage::SearchResultInFocusChangedLocationMessage(const Eegeo::v2& screenLocation)
			: m_screenLocation(screenLocation)
		{

		}

		const Eegeo::v2& SearchResultInFocusChangedLocationMessage::ScreenLocation() const
		{
			return m_screenLocation;
		}
	}
}
