// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "Compass.h"
#include "CompassViewIncludes.h"
#include "ScreenControlViewModelIncludes.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace Compass
    {
    	class CompassViewController : private Eegeo::NonCopyable
		{
    		AndroidNativeState& m_nativeState;

    		jclass m_uiViewClass;
    		jobject m_uiView;

    		Compass::ICompassModel& m_model;
    		Compass::ICompassViewModel& m_viewModel;

    		Eegeo::Helpers::ICallback0* m_pGpsModelChangedCallback;
    		Eegeo::Helpers::ICallback1<float>* m_pUpdateCallback;
    		Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>* m_pOnScreenStateChangedCallback;

		public:
    		CompassViewController(
					AndroidNativeState& nativeState,
	        		Compass::ICompassModel& model,
					Compass::ICompassViewModel& menuViewModel
			);

    		~CompassViewController();

    		void HandleClick();

		private:
			void OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel &viewModel, float& onScreenState);

			void OnHeadingUpdated(float& headingAngleRadians);

			void OnGpsModeChanged();
		};
    }
}
