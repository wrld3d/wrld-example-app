// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "AndroidNativeState.h"
#include "MyPinCreationDetails.h"
#include "MyPinCreation.h"
#include "ICallback.h"
#include "UiToNativeMessageBus.h"
#include <string>

namespace ExampleApp
{
	namespace MyPinCreationDetails
	{
		class MyPinCreationDetailsViewController
		{
		public:
			MyPinCreationDetailsViewController(
				AndroidNativeState& nativeState,
	           	MyPinCreation::IMyPinCreationModel& model,
	          	MyPinCreationDetails::IMyPinCreationDetailsViewModel& viewModel,
				ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus
			);
			~MyPinCreationDetailsViewController();

			void Open();
			void Close();
			void HandleCloseButtonPressed();
			void HandleConfirmButtonPressed(std::string title,
											std::string description,
											std::string imagePath,
							    			Byte* pImageBytes,
							    			size_t imageSize,
											bool shouldShare);

		private:

			AndroidNativeState& m_nativeState;

			jclass m_uiViewClass;
			jobject m_uiView;

			MyPinCreation::IMyPinCreationModel& m_model;
			MyPinCreationDetails::IMyPinCreationDetailsViewModel& m_viewModel;
			ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;

			Eegeo::Helpers::ICallback0* m_pOpenedCallback;
			Eegeo::Helpers::ICallback0* m_pClosedCallback;
		};

	}
}
