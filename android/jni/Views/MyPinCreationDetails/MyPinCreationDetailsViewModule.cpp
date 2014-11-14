// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinCreationDetailsViewModule.h"
#include "MyPinCreationDetailsViewController.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
    	MyPinCreationDetailsViewModule::MyPinCreationDetailsViewModule(
            	AndroidNativeState& nativeState,
            	MyPinCreation::IMyPinCreationModel& model,
            	MyPinCreationDetails::IMyPinCreationDetailsViewModel& viewModel,
			    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus
            )
    	{
    		m_pViewController = Eegeo_NEW(MyPinCreationDetailsViewController)(
    				nativeState,
    				model,
    				viewModel,
    				uiToNativeMessageBus
    			);
    	}

    	MyPinCreationDetailsViewModule::~MyPinCreationDetailsViewModule()
    	{
    		Eegeo_DELETE m_pViewController;
    	}
    }
}
