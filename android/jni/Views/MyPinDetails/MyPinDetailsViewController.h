// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPinDetails.h"
#include "Types.h"
#include "AndroidNativeState.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
    	class MyPinDetailsViewController
    	{
		public:

    		MyPinDetailsViewController(
    				AndroidNativeState& nativeState,
    				IMyPinDetailsViewModel& myPinDetailsViewModel);
    		~MyPinDetailsViewController();

    		void Open();
    		void Close();
    		void HandleCloseButtonPressed();

		private:

    		AndroidNativeState& m_nativeState;

			jclass m_uiViewClass;
			jobject m_uiView;

    		IMyPinDetailsViewModel& m_viewModel;

    		Eegeo::Helpers::ICallback0* m_pOpenedCallback;
    		Eegeo::Helpers::ICallback0* m_pClosedCallback;
    	};
    }
}
