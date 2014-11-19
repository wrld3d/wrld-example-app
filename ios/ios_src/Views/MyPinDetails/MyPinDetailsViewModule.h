// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "MyPinDetails.h"
#include "IMyPinDetailsViewModule.h"
#include "UiToNativeMessageBus.h"

namespace ExampleApp
{
	namespace MyPinDetails
	{
		class MyPinDetailsViewModule: public IMyPinDetailsViewModule, private Eegeo::NonCopyable
		{
		private:
			MyPinDetailsViewController* m_pMyPinDetailsViewController;

		public:
			MyPinDetailsViewModule(ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
                                   IMyPinDetailsViewModel& MyPinDetailsViewModel);

			~MyPinDetailsViewModule();

			MyPinDetailsViewController& GetMyPinDetailsViewController() const;

			MyPinDetailsView& GetMyPinDetailsView() const;
		};
	}
}
