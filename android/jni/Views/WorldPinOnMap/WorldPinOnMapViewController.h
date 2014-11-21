// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include "AndroidNativeState.h"
#include "Types.h"
#include "WorldPins.h"
#include "ICallback.h"
#include "IWorldPinInFocusViewModel.h"
#include "IScreenControlViewModel.h"
#include "Modality.h"

namespace ExampleApp
{
	namespace WorldPins
	{
		class WorldPinOnMapViewController : private Eegeo::NonCopyable
		{
			AndroidNativeState& m_nativeState;
			IWorldPinInFocusViewModel& m_worldPinInFocusViewModel;
			ScreenControlViewModel::IScreenControlViewModel& m_worldPinScreenControlViewModel;
			const Modality::IModalityModel& m_modalityModel;

			Eegeo::Helpers::TCallback0<WorldPinOnMapViewController> m_worldPinOnMapFocusOpenedCallback;
			Eegeo::Helpers::TCallback0<WorldPinOnMapViewController> m_worldPinOnMapFocusClosedCallback;
			Eegeo::Helpers::TCallback0<WorldPinOnMapViewController> m_worldPinOnMapFocusUpdatedCallback;
			Eegeo::Helpers::TCallback2<WorldPinOnMapViewController, ScreenControlViewModel::IScreenControlViewModel&, float> m_screenStateChangedCallback;

			jclass m_uiViewClass;
			jobject m_uiView;
			const float m_pinOffset;

		public:
			WorldPinOnMapViewController(
			    AndroidNativeState& nativeState,
			    IWorldPinInFocusViewModel& worldPinInFocusViewModel,
			    ScreenControlViewModel::IScreenControlViewModel& worldPinScreenControlViewModel,
			    const Modality::IModalityModel& modalityModel,
			    float pinDiameter
			);

			~WorldPinOnMapViewController();

			void HandleWorldPinOnMapClicked();

		private:

			void WorldPinOnMapFocusOpenedCallback();

			void WorldPinOnMapFocusClosedCallback();

			void WorldPinOnMapFocusUpdatedCallback();

			void ScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel& screenControlViewModel, float& screenState);
		};
	}
}
