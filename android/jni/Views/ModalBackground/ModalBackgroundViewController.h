// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "Modality.h"
#include "ModalBackgroundViewModule.h"
#include "IModalBackgroundViewController.h"
#include "ModalBackgroundView.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
		class ModalBackgroundViewController : public IModalBackgroundViewController, private Eegeo::NonCopyable
		{
			AndroidNativeState& m_nativeState;
			Modality::IModalityModel& m_modalityModel;
			ModalBackgroundView& m_modalBackgroundView;

			jclass m_uiViewClass;
			jobject m_uiView;

			Eegeo::Helpers::ICallback0* m_pOpenStateChangedCallback;

		public:
		    ModalBackgroundViewController(
				AndroidNativeState& nativeState,
				Modality::IModalityModel& modalityModel,
				ModalBackgroundView& modalBackgroundView
			);

			~ModalBackgroundViewController();

		private:

		    void OpenStateChangedCallback();
		};
    }
}
