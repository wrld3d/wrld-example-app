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
			ExampleAppMessaging::UiToNativeMessageBus& m_messageBus;
			Eegeo::Helpers::TCallback1<SearchResultMenuItemSelectedMessageHandler, const SearchResultMenuItemSelectedMessage&> m_handleSearchResultMenuItemSelectedMessageBinding;

			void HandleReceivedSearchResultMenuItemSelectedMessage(const SearchResultMenuItemSelectedMessage& message)
			{
				const float newDistanceFromInterest = 1000;
				m_cameraTransitionController.StartTransitionTo(message.SearchResultLocationEcef(), newDistanceFromInterest);
			}

		public:
			SearchResultMenuItemSelectedMessageHandler(
			    CameraTransitions::ICameraTransitionController& cameraTransitionController,
			    ExampleAppMessaging::UiToNativeMessageBus& messageBus)
				: m_cameraTransitionController(cameraTransitionController)
				, m_messageBus(messageBus)
				, m_handleSearchResultMenuItemSelectedMessageBinding(this, &SearchResultMenuItemSelectedMessageHandler::HandleReceivedSearchResultMenuItemSelectedMessage)
			{
				m_messageBus.Subscribe(m_handleSearchResultMenuItemSelectedMessageBinding);
			}

			~SearchResultMenuItemSelectedMessageHandler()
			{
				m_messageBus.Unsubscribe(m_handleSearchResultMenuItemSelectedMessageBinding);
			}
		};
	}
}
