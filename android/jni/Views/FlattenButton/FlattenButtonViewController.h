// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "FlattenButton.h"
#include "FlattenButtonViewIncludes.h"
#include "ScreenControlViewModelIncludes.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
    	class FlattenButtonViewController : private Eegeo::NonCopyable
		{

		public:
    		FlattenButtonViewController(
					AndroidNativeState& nativeState,
					FlattenButton::IFlattenButtonModel& model,
					FlattenButton::IFlattenButtonViewModel& menuViewModel
			);

    		~FlattenButtonViewController();

    		void SetFlattened(bool flattened);

		private:

    		AndroidNativeState& m_nativeState;

    		jclass m_uiViewClass;
    		jobject m_uiView;

			FlattenButton::IFlattenButtonModel& m_model;
    		ExampleApp::FlattenButton::IFlattenButtonViewModel& m_viewModel;

            Eegeo::Helpers::ICallback0* m_pFlattenModelStateChangedCallback;
    		Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>* m_pOnScreenStateChangedCallback;

    		void OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel& viewModel, float& onScreenState);

            void OnFlattenModelStateChangedCallback();
		};
    }
}
