//  Copyright (c) 2014 eeGeo. All rights reserved.

#pragma once

#include "CompassGpsMode.h"

namespace ExampleApp
{
namespace Compass
{
class CompassModeChangedMessage
{
private:
	GpsMode::Values m_mode;

public:
	CompassModeChangedMessage(GpsMode::Values mode)
		: m_mode(mode)
	{
	}

	GpsMode::Values GetMode() const
	{
		return m_mode;
	}
};
}
}