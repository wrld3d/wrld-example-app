// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Menu.h"
#include "PlaceJumps.h"

namespace ExampleApp
{
	namespace PlaceJumps
	{
		class IPlaceJumpsModule
		{
		public:
			virtual ~IPlaceJumpsModule() { }

			virtual Menu::IMenuModel& GetPlaceJumpsMenuModel() const = 0;
			virtual IPlaceJumpController& GetPlaceJumpController() const = 0;
		};
	}
}
