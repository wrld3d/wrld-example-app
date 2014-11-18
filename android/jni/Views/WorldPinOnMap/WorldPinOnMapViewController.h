// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include "AndroidNativeState.h"
#include "Types.h"
#include "WorldPins.h"
#include "ICallback.h"
#include "IWorldPinInFocusViewModel.h"
#include "IScreenControlViewModel.h"

namespace ExampleApp
{
	namespace WorldPins
	{
		class WorldPinOnMapViewController : private Eegeo::NonCopyable
		{
			AndroidNativeState& m_nativeState;
			IWorldPinInFocusViewModel& m_worldPinInFocusViewModel;
			ScreenControlViewModel::IScreenControlViewModel& m_worldPinScreenControlViewModel;

			Eegeo::Helpers::TCallback0<WorldPinOnMapViewController> m_worldPinOnMapFocusOpenedCallback;
			Eegeo::Helpers::TCallback0<WorldPinOnMapViewController> m_worldPinOnMapFocusClosedCallback;
			Eegeo::Helpers::TCallback0<WorldPinOnMapViewController> m_worldPinOnMapFocusUpdatedCallback;

			jclass m_uiViewClass;
			jobject m_uiView;
			const float m_pinOffset;

		public:
			WorldPinOnMapViewController(
			    AndroidNativeState& nativeState,
			    IWorldPinInFocusViewModel& worldPinInFocusViewModel,
			    ScreenControlViewModel::IScreenControlViewModel& worldPinScreenControlViewModel,
			    float pinDiameter
			);

			~WorldPinOnMapViewController();

			void HandleWorldPinOnMapClicked();

		private:

			void WorldPinOnMapFocusOpenedCallback();

			void WorldPinOnMapFocusClosedCallback();

			void WorldPinOnMapFocusUpdatedCallback();
		};
	}
}
