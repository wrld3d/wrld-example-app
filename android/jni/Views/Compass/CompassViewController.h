// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "Compass.h"
#include "CompassViewIncludes.h"
#include "ScreenControlViewModelIncludes.h"
#include "ICallback.h"
#include "CompassModeChangedMessage.h"
#include "CompassHeadingUpdateMessage.h"
#include "NativeToUiMessageBus.h"
#include "UiToNativeMessageBus.h"

namespace ExampleApp
{
    namespace Compass
    {
    	class CompassViewController : private Eegeo::NonCopyable
		{
    		AndroidNativeState& m_nativeState;

    		jclass m_uiViewClass;
    		jobject m_uiView;

    		Compass::ICompassViewModel& m_viewModel;

            ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
			ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;

            Eegeo::Helpers::TCallback2<CompassViewController, ScreenControlViewModel::IScreenControlViewModel&, float> m_onScreenStateChangedCallback;
            Eegeo::Helpers::TCallback1<CompassViewController, const CompassModeChangedMessage&> m_modeChangedCallback;
            Eegeo::Helpers::TCallback1<CompassViewController, const CompassHeadingUpdateMessage&> m_headingChangedCallback;

		public:
    		CompassViewController(
					AndroidNativeState& nativeState,
					Compass::ICompassViewModel& menuViewModel,
                    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
					ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus
			);

    		~CompassViewController();

    		void HandleClick();

		private:
            void OnCompassModeChanged(const CompassModeChangedMessage& message);

            void OnCompassHeadingChanged(const CompassHeadingUpdateMessage& message);

			void OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel &viewModel, float& onScreenState);
		};
    }
}
