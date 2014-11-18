// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "VectorMath.h"

namespace ExampleApp
{
	namespace WorldPins
	{
		class WorldPinInFocusChangedLocationMessage
		{
			Eegeo::v2 m_screenLocation;

		public:
			WorldPinInFocusChangedLocationMessage(const Eegeo::v2& screenLocation)
				: m_screenLocation(screenLocation)
			{

			}

			const Eegeo::v2& ScreenLocation() const
			{
				return m_screenLocation;
			}
		};
	}
}
