//  Copyright (c) 2014 eeGeo. All rights reserved.

#pragma once

namespace ExampleApp
{
namespace Compass
{
class CompassHeadingUpdateMessage
{
private:
	float m_headingRadians;

public:
	CompassHeadingUpdateMessage(float headingRadians)
		: m_headingRadians(headingRadians)
	{
	}

	float GetHeadingRadians() const
	{
		return m_headingRadians;
	}
};
}
}