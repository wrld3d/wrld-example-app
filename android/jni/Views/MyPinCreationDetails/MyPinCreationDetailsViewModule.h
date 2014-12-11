// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMyPinCreationDetailsViewModule.h"
#include "Types.h"
#include "AndroidNativeState.h"
#include "MyPinCreationDetails.h"
#include "MyPinCreation.h"
#include "MyPinCreationDetailsViewIncludes.h"
#include "UiToNativeMessageBus.h"
#include "IConnectivityService.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
    	class MyPinCreationDetailsViewModule : public IMyPinCreationDetailsViewModule, private Eegeo::NonCopyable
        {
        private:
    		MyPinCreationDetailsViewController* m_pViewController;

        public:
    		MyPinCreationDetailsViewModule(
            	AndroidNativeState& nativeState,
            	MyPinCreation::IMyPinCreationModel& model,
            	MyPinCreationDetails::IMyPinCreationDetailsViewModel& viewModel,
			    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
			    Eegeo::Web::IConnectivityService& connectivityService
            );

            ~MyPinCreationDetailsViewModule();
        };
    }
}
