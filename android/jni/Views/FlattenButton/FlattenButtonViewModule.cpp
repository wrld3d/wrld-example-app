// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "FlattenButtonViewModule.h"
#include "FlattenButtonViewController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
    	FlattenButtonViewModule::FlattenButtonViewModule(
            	AndroidNativeState& nativeState,
        		FlattenButton::IFlattenButtonViewModel& viewModel,
				ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
				ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus
            )
    	{
    		ASSERT_UI_THREAD

    		m_pController = Eegeo_NEW(FlattenButtonViewController)(
				nativeState,
				viewModel,
				uiToNativeMessageBus,
				nativeToUiMessageBus
			);
    	}

    	FlattenButtonViewModule::~FlattenButtonViewModule()
    	{
    		ASSERT_UI_THREAD

    		Eegeo_DELETE m_pController;
    	}
    }
}
