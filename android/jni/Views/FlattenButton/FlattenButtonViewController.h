// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "FlattenButton.h"
#include "FlattenButtonViewIncludes.h"
#include "ScreenControlViewModelIncludes.h"
#include "ICallback.h"
#include "UiToNativeMessageBus.h"
#include "NativeToUiMessageBus.h"
#include "FlattenButtonModelStateChangedMessage.h"

namespace ExampleApp
{
	namespace FlattenButton
	{
		class FlattenButtonViewController : private Eegeo::NonCopyable
		{

		public:
			FlattenButtonViewController(
			    AndroidNativeState& nativeState,
			    FlattenButton::IFlattenButtonViewModel& menuViewModel,
			    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
			    ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus
			);

			~FlattenButtonViewController();

			void SetFlattened(bool flattened);

		private:

			AndroidNativeState& m_nativeState;

			jclass m_uiViewClass;
			jobject m_uiView;

			ExampleApp::FlattenButton::IFlattenButtonViewModel& m_viewModel;
			ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
			ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;

			Eegeo::Helpers::TCallback1<FlattenButtonViewController, const FlattenButtonModelStateChangedMessage&> m_flattenModelStateChangedCallback;
			Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>* m_pOnScreenStateChangedCallback;

			void OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel& viewModel, float& onScreenState);

			void OnFlattenModelStateChangedCallback(const FlattenButtonModelStateChangedMessage& message);
		};
	}
}
