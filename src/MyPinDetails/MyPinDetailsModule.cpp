// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinDetailsModule.h"
#include "MyPinDetailsViewModel.h"
#include "MyPinDetailsModelSelectedObserver.h"

namespace ExampleApp
{
	namespace MyPinDetails
	{
		MyPinDetailsModule::MyPinDetailsModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                               Reaction::IReactionControllerModel& reactionControllerModel,
                                               ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
		{
			m_pMyPinDetailsViewModel = Eegeo_NEW(MyPinDetailsViewModel)(identityProvider.GetNextIdentity(),
			                              reactionControllerModel);
            
            m_pMyPinDetailsModelSelectedObserver = Eegeo_NEW(MyPinDetailsModelSelectedObserver)(*m_pMyPinDetailsViewModel,
                                                                                                nativeToUiMessageBus);
		}

		MyPinDetailsModule::~MyPinDetailsModule()
		{
            Eegeo_DELETE m_pMyPinDetailsModelSelectedObserver;
			Eegeo_DELETE m_pMyPinDetailsViewModel;
		}

		IMyPinDetailsViewModel& MyPinDetailsModule::GetMyPinDetailsViewModel() const
		{
			return *m_pMyPinDetailsViewModel;
		}

		OpenableControlViewModel::IOpenableControlViewModel& MyPinDetailsModule::GetObservableOpenableControl() const
		{
			return m_pMyPinDetailsViewModel->GetOpenableControl();
		}
	}
}
