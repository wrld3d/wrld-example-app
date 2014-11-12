// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

namespace ExampleApp
{
namespace Compass
{
class ICompassUpdateController
{
public:
	virtual ~ICompassUpdateController() { }

	virtual void Update(float deltaSeconds) = 0;
};
}
}
