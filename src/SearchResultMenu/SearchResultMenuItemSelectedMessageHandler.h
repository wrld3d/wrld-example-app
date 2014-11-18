// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "UiToNativeMessageBus.h"
#include "ICallback.h"
#include "SearchResultMenuItemSelectedMessage.h"
#include "ICameraTransitionController.h"

namespace ExampleApp
{
	namespace SearchResultMenu
	{
		class SearchResultMenuItemSelectedMessageHandler : private Eegeo::NonCopyable
		{
			CameraTransitions::ICameraTransitionController& m_cameraTransitionController;
			ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
			Eegeo::Helpers::TCallback1<SearchResultMenuItemSelectedMessageHandler, const SearchResultMenuItemSelectedMessage&> m_handleSearchResultMenuItemSelectedMessageBinding;

			void HandleReceivedSearchResultMenuItemSelectedMessage(const SearchResultMenuItemSelectedMessage& message);

		public:
			SearchResultMenuItemSelectedMessageHandler(
			    CameraTransitions::ICameraTransitionController& cameraTransitionController,
			    ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);

			~SearchResultMenuItemSelectedMessageHandler();
		};
	}
}
