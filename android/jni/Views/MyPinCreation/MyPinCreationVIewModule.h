// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMyPinCreationViewModule.h"
#include "Types.h"
#include "AndroidNativeState.h"
#include "MyPinCreation.h"
#include "MyPinCreationDetails.h"
#include "MyPinCreationViewIncludes.h"
#include "UiToNativeMessageBus.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
    	class MyPinCreationViewModule : public IMyPinCreationViewModule, private Eegeo::NonCopyable
        {
        private:
        	MyPinCreationInitiationViewController* m_pInitiationViewController;
        	MyPinCreationConfirmationViewController* m_pConfirmationViewController;

        public:
        	MyPinCreationViewModule(
            	AndroidNativeState& nativeState,
            	MyPinCreation::IMyPinCreationModel& model,
            	MyPinCreation::IMyPinCreationInitiationViewModel& initiationViewModel,
            	MyPinCreation::IMyPinCreationConfirmationViewModel& confirmationViewModel,
            	MyPinCreationDetails::IMyPinCreationDetailsViewModel& detailsViewModel,
			    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus
            );

            ~MyPinCreationViewModule();
        };
    }
}
