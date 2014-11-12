// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "PoiCreation.h"
#include "PoiCreationDetails.h"
#include "ICallback.h"
#include "ScreenControlViewModelIncludes.h"
#include "PoiCreationViewIncludes.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
    	class PoiCreationConfirmationViewController : private Eegeo::NonCopyable
		{

		public:
    		PoiCreationConfirmationViewController(
					AndroidNativeState& nativeState,
					PoiCreation::IPoiCreationModel& model,
					PoiCreation::IPoiCreationConfirmationViewModel& viewModel,
					PoiCreationDetails::IPoiCreationDetailsViewModel& detailsViewModel
			);

    		void HandleCancelSelected();
    		void HandleConfirmSelected();

    		~PoiCreationConfirmationViewController();

		private:

    		AndroidNativeState& m_nativeState;

    		jclass m_uiViewClass;
    		jobject m_uiView;

    		PoiCreation::IPoiCreationModel& m_model;
    		PoiCreation::IPoiCreationConfirmationViewModel& m_viewModel;
    		PoiCreationDetails::IPoiCreationDetailsViewModel& m_detailsViewModel;

    		Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>* m_pOnScreenStateChangedCallback;

    		void OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel& viewModel, float& onScreenState);
		};
    }
}
