// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Compass.h"
#include "ScreenControlViewModelIncludes.h"

namespace ExampleApp
{
namespace Compass
{
class ICompassModule
{
public:
	virtual ~ICompassModule() { }

	virtual ICompassModel& GetCompassModel() const = 0;

	virtual ICompassViewModel& GetCompassViewModel() const = 0;

	virtual ICompassUpdateController& GetCompassUpdateController() const = 0;

	virtual ScreenControlViewModel::IScreenControlViewModel& GetScreenControlViewModel() const = 0;
};
}
}
