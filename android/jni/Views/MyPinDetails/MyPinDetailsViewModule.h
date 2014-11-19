// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMyPinDetailsViewModule.h"
#include "MyPinDetailsViewIncludes.h"
#include "AndroidNativeState.h"
#include "MyPinDetails.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
		class MyPinDetailsViewModule : public IMyPinDetailsViewModule
		{
		public:
			MyPinDetailsViewModule(
					AndroidNativeState& nativeState,
    				IMyPinDetailsViewModel& myPinDetailsViewModel);
			~MyPinDetailsViewModule();

		private:

			MyPinDetailsViewController* m_pViewController;

		};
    }
}
