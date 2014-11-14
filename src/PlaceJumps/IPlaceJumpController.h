// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Menu.h"
#include "PlaceJumps.h"
#include "GlobeCamera.h"

namespace ExampleApp
{
	namespace PlaceJumps
	{
		class IPlaceJumpController
		{
		public:
			virtual ~IPlaceJumpController() { }

			virtual void JumpTo(IPlaceJumpModel& jumpModel) = 0;
		};
	}
}
