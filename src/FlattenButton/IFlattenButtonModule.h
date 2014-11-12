// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "FlattenButton.h"
#include "ScreenControlViewModelIncludes.h"

namespace ExampleApp
{
	namespace FlattenButton
	{
		class IFlattenButtonModule
		{
		public:
			virtual ~IFlattenButtonModule() { }

			virtual IFlattenButtonModel& GetFlattenButtonModel() const = 0;

			virtual IFlattenButtonViewModel& GetFlattenButtonViewModel() const = 0;

			virtual ScreenControlViewModel::IScreenControlViewModel& GetScreenControlViewModel() const = 0;
		};
	}
}
