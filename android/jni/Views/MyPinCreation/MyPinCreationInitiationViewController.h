// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "MyPinCreation.h"
#include "ICallback.h"
#include "ScreenControlViewModelIncludes.h"
#include "MyPinCreationViewIncludes.h"
#include "UiToNativeMessageBus.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
    	class MyPinCreationInitiationViewController : private Eegeo::NonCopyable
		{

		public:
    		MyPinCreationInitiationViewController(
					AndroidNativeState& nativeState,
					MyPinCreation::IMyPinCreationModel& model,
					MyPinCreation::IMyPinCreationInitiationViewModel& viewModel,
					ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus
			);

    		void Selected();

    		~MyPinCreationInitiationViewController();

		private:

    		AndroidNativeState& m_nativeState;

    		jclass m_uiViewClass;
    		jobject m_uiView;

    		MyPinCreation::IMyPinCreationModel& m_model;
    		MyPinCreation::IMyPinCreationInitiationViewModel& m_viewModel;
    		ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;

    		Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>* m_pOnScreenStateChangedCallback;

    		void OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel& viewModel, float& onScreenState);
		};
    }
}
