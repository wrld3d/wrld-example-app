// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "PoiCreation.h"
#include "ICallback.h"
#include "ScreenControlViewModelIncludes.h"
#include "PoiCreationViewIncludes.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
    	class PoiCreationButtonViewController : private Eegeo::NonCopyable
		{

		public:
    		PoiCreationButtonViewController(
					AndroidNativeState& nativeState,
					PoiCreation::IPoiCreationModel& model,
					PoiCreation::IPoiCreationButtonViewModel& viewModel
			);

    		void Selected();

    		~PoiCreationButtonViewController();

		private:

    		AndroidNativeState& m_nativeState;

    		jclass m_uiViewClass;
    		jobject m_uiView;

    		PoiCreation::IPoiCreationModel& m_model;
    		PoiCreation::IPoiCreationButtonViewModel& m_viewModel;

    		Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>* m_pOnScreenStateChangedCallback;

    		void OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel& viewModel, float& onScreenState);
		};
    }
}
