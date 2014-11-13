//  Copyright (c) 2014 eeGeo. All rights reserved.

#include "CompassModeChangedMessage.h"

namespace ExampleApp
{
	namespace Compass
	{
		CompassModeChangedMessage::CompassModeChangedMessage(GpsMode::Values mode)
			: m_mode(mode)
		{
		}

		GpsMode::Values CompassModeChangedMessage::GetMode() const
		{
			return m_mode;
		}
	}
}
