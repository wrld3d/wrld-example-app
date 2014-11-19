// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPinDetails.h"
#include "IOpenableControlViewModel.h"

namespace ExampleApp
{
	namespace MyPinDetails
	{
		class IMyPinDetailsModule
		{
		public:
			virtual ~IMyPinDetailsModule() { }

			virtual IMyPinDetailsViewModel& GetMyPinDetailsViewModel() const = 0;

			virtual OpenableControlViewModel::IOpenableControlViewModel& GetObservableOpenableControl() const = 0;
		};
	}
}
