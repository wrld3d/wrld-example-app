// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "MyPinDetails.h"
#include "IMyPinDetailsModule.h"
#include "MyPinDetailsViewModel.h"
#include "IIdentity.h"
#include "Reaction.h"
#include "NativeToUiMessageBus.h"

namespace ExampleApp
{
	namespace MyPinDetails
	{
		class MyPinDetailsModule: public IMyPinDetailsModule, private Eegeo::NonCopyable
		{
		private:
			MyPinDetailsViewModel* m_pMyPinDetailsViewModel;
            MyPinDetailsModelSelectedObserver* m_pMyPinDetailsModelSelectedObserver;
            
		public:
			MyPinDetailsModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                               Reaction::IReactionControllerModel& reactionControllerModel,
                               ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);

			~MyPinDetailsModule();

			IMyPinDetailsViewModel& GetMyPinDetailsViewModel() const;

			OpenableControlViewModel::IOpenableControlViewModel& GetObservableOpenableControl() const;
		};
	}
}
