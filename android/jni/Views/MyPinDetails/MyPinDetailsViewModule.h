// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMyPinDetailsViewModule.h"
#include "MyPinDetailsViewIncludes.h"
#include "AndroidNativeState.h"
#include "MyPinDetails.h"
#include "UiToNativeMessageBus.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
		class MyPinDetailsViewModule : public IMyPinDetailsViewModule
		{
		public:
			MyPinDetailsViewModule(
					AndroidNativeState& nativeState,
    				IMyPinDetailsViewModel& myPinDetailsViewModel,
    			    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);
			~MyPinDetailsViewModule();

		private:

			MyPinDetailsViewController* m_pViewController;

		};
    }
}
