// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "WorldPinOnMapViewIncludes.h"

namespace ExampleApp
{
	namespace WorldPins
	{
		class IWorldPinOnMapViewModule
		{
		public:
			virtual ~IWorldPinOnMapViewModule() { }

			virtual WorldPinOnMapViewController& GetWorldPinOnMapViewController() const = 0;
		};
	}
}
