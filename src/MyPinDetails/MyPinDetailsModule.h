// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "MyPinDetails.h"
#include "IMyPinDetailsModule.h"
#include "MyPinDetailsViewModel.h"
#include "IIdentity.h"
#include "Reaction.h"
#include "NativeToUiMessageBus.h"
#include "UiToNativeMessageBus.h"
#include "MyPinDetailsViewRemovePinHandler.h"

namespace ExampleApp
{
	namespace MyPinDetails
	{
		class MyPinDetailsModule: public IMyPinDetailsModule, private Eegeo::NonCopyable
		{
		private:
			MyPinDetailsViewModel* m_pMyPinDetailsViewModel;
            MyPinDetailsModelSelectedObserver* m_pMyPinDetailsModelSelectedObserver;
            MyPinDetailsViewRemovePinHandler* m_pMyPinDetailsViewRemovePinHandler;
            
		public:
			MyPinDetailsModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                               Reaction::IReactionControllerModel& reactionControllerModel,
                               MyPins::IMyPinsService& myPinsService,
                               ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus,
                               ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);

			~MyPinDetailsModule();

			IMyPinDetailsViewModel& GetMyPinDetailsViewModel() const;

			OpenableControlViewModel::IOpenableControlViewModel& GetObservableOpenableControl() const;
		};
	}
}
