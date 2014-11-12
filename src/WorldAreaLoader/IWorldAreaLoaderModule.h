// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "WorldAreaLoader.h"

namespace ExampleApp
{
namespace WorldAreaLoader
{
class IWorldAreaLoaderModule
{
public:
	virtual ~IWorldAreaLoaderModule() { }

	virtual IWorldAreaLoaderModel& GetWorldAreaLoaderModel() const = 0;
};
}
}
