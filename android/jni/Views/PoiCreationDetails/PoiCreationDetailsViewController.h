// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "AndroidNativeState.h"
#include "PoiCreationDetails.h"
#include "PoiCreation.h"
#include "ICallback.h"
#include <string>

namespace ExampleApp
{
	namespace PoiCreationDetails
	{
		class PoiCreationDetailsViewController
		{
		public:
			PoiCreationDetailsViewController(
				AndroidNativeState& nativeState,
	           	PoiCreation::IPoiCreationModel& model,
	          	PoiCreationDetails::IPoiCreationDetailsViewModel& viewModel
			);
			~PoiCreationDetailsViewController();

			void Open();
			void Close();
			void HandleCloseButtonPressed();
			void HandleConfirmButtonPressed(std::string title,
											std::string description,
											std::string image,
											bool shouldShare);

		private:

			AndroidNativeState& m_nativeState;

			jclass m_uiViewClass;
			jobject m_uiView;

			PoiCreation::IPoiCreationModel& m_model;
			PoiCreationDetails::IPoiCreationDetailsViewModel& m_viewModel;

			Eegeo::Helpers::ICallback0* m_pOpenedCallback;
			Eegeo::Helpers::ICallback0* m_pClosedCallback;
		};

	}
}
