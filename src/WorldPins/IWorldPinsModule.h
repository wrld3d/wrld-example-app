// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "WorldPins.h"

namespace ExampleApp
{
	namespace WorldPins
	{
		class IWorldPinsModule
		{
		public:
			virtual ~IWorldPinsModule() { }

			virtual IWorldPinsService& GetWorldPinsService() const = 0;
		};
	}
}
