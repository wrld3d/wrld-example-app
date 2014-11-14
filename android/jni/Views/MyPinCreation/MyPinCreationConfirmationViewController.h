// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "MyPinCreation.h"
#include "MyPinCreationDetails.h"
#include "ICallback.h"
#include "ScreenControlViewModelIncludes.h"
#include "MyPinCreationViewIncludes.h"
#include "UiToNativeMessageBus.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
    	class MyPinCreationConfirmationViewController : private Eegeo::NonCopyable
		{

		public:
    		MyPinCreationConfirmationViewController(
					AndroidNativeState& nativeState,
					MyPinCreation::IMyPinCreationModel& model,
					MyPinCreation::IMyPinCreationConfirmationViewModel& viewModel,
					MyPinCreationDetails::IMyPinCreationDetailsViewModel& detailsViewModel,
					ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus
			);

    		void HandleCancelSelected();
    		void HandleConfirmSelected();

    		~MyPinCreationConfirmationViewController();

		private:

    		AndroidNativeState& m_nativeState;

    		jclass m_uiViewClass;
    		jobject m_uiView;

    		MyPinCreation::IMyPinCreationModel& m_model;
    		MyPinCreation::IMyPinCreationConfirmationViewModel& m_viewModel;
    		MyPinCreationDetails::IMyPinCreationDetailsViewModel& m_detailsViewModel;
    		ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;

    		Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>* m_pOnScreenStateChangedCallback;

    		void OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel& viewModel, float& onScreenState);
		};
    }
}
