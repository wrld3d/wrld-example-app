// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPinDetailsViewIncludes.h"

namespace ExampleApp
{
	namespace MyPinDetails
	{
		class IMyPinDetailsViewModule
		{
		public:
			virtual ~IMyPinDetailsViewModule() { }

			virtual MyPinDetailsViewController& GetMyPinDetailsViewController() const = 0;

			virtual MyPinDetailsView& GetMyPinDetailsView() const = 0;
		};
	}
}
