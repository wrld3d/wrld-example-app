//  Copyright (c) 2014 eeGeo. All rights reserved.

#include "CompassHeadingUpdateMessage.h"

namespace ExampleApp
{
	namespace Compass
	{
		CompassHeadingUpdateMessage::CompassHeadingUpdateMessage(float headingRadians)
		: m_headingRadians(headingRadians)
		{
		}

		float CompassHeadingUpdateMessage::GetHeadingRadians() const
		{
			return m_headingRadians;
		}
	}
}
