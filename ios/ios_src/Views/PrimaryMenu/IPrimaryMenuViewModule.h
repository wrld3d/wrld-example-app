// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "PrimaryMenuViewIncludes.h"

namespace ExampleApp
{
	namespace PrimaryMenu
	{
		class IPrimaryMenuViewModule
		{
		public:
			virtual ~IPrimaryMenuViewModule() { }

			virtual MenuViewController& GetPrimaryMenuViewController() const = 0;

			virtual PrimaryMenuView& GetPrimaryMenuView() const = 0;
		};
	}
}
