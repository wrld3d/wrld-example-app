// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinCreationViewModule.h"
#include "MyPinCreationInitiationViewController.h"
#include "MyPinCreationConfirmationViewController.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
    	MyPinCreationViewModule::MyPinCreationViewModule(
            	AndroidNativeState& nativeState,
            	MyPinCreation::IMyPinCreationModel& model,
            	MyPinCreation::IMyPinCreationInitiationViewModel& initiationViewModel,
            	MyPinCreation::IMyPinCreationConfirmationViewModel& confirmationViewModel,
            	MyPinCreationDetails::IMyPinCreationDetailsViewModel& detailsViewModel,
			    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus
            )
    	{
    		m_pInitiationViewController = Eegeo_NEW(MyPinCreationInitiationViewController)(nativeState, model, initiationViewModel, confirmationViewModel, uiToNativeMessageBus);
    		m_pConfirmationViewController = Eegeo_NEW(MyPinCreationConfirmationViewController)(nativeState, model, confirmationViewModel, detailsViewModel, uiToNativeMessageBus);
    	}

    	MyPinCreationViewModule::~MyPinCreationViewModule()
    	{
    		Eegeo_DELETE m_pConfirmationViewController;
    		Eegeo_DELETE m_pInitiationViewController;
    	}
    }
}
