// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "SecondaryMenuViewIncludes.h"

namespace ExampleApp
{
	namespace SecondaryMenu
	{
		class ISecondaryMenuViewModule
		{
		public:
			virtual ~ISecondaryMenuViewModule() { }

			virtual MenuViewController& GetSecondaryMenuViewController() const = 0;

			virtual SecondaryMenuView& GetSecondaryMenuView() const = 0;
		};
	}
}
