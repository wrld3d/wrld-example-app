// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinDetailsViewModule.h"
#include "IMyPinDetailsViewModel.h"
#include "MyPinDetailsViewController.h"

namespace ExampleApp
{
	namespace MyPinDetails
	{
		MyPinDetailsViewModule::MyPinDetailsViewModule(ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
                                                       IMyPinDetailsViewModel& MyPinDetailsViewModel)
		{
			m_pMyPinDetailsViewController = [[MyPinDetailsViewController alloc] initWithParams :&uiToNativeMessageBus
                                                                                               :&MyPinDetailsViewModel];
		}

		MyPinDetailsViewModule::~MyPinDetailsViewModule()
		{
			[m_pMyPinDetailsViewController release];
		}

		MyPinDetailsViewController& MyPinDetailsViewModule::GetMyPinDetailsViewController() const
		{
			return *m_pMyPinDetailsViewController;
		}

		MyPinDetailsView& MyPinDetailsViewModule::GetMyPinDetailsView() const
		{
			return *[m_pMyPinDetailsViewController pMyPinDetailsView];
		}
	}
}
