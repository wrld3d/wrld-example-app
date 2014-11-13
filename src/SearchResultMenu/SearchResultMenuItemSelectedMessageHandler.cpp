// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultMenuItemSelectedMessageHandler.h"

namespace ExampleApp
{
	namespace SearchResultMenu
	{
		void SearchResultMenuItemSelectedMessageHandler::HandleReceivedSearchResultMenuItemSelectedMessage(const SearchResultMenuItemSelectedMessage& message)
		{
			const float newDistanceFromInterest = 1000;
			m_cameraTransitionController.StartTransitionTo(message.SearchResultLocationEcef(), newDistanceFromInterest);
		}

		SearchResultMenuItemSelectedMessageHandler::SearchResultMenuItemSelectedMessageHandler(
			CameraTransitions::ICameraTransitionController& cameraTransitionController,
			ExampleAppMessaging::UiToNativeMessageBus& messageBus)
			: m_cameraTransitionController(cameraTransitionController)
			, m_messageBus(messageBus)
			, m_handleSearchResultMenuItemSelectedMessageBinding(this, &SearchResultMenuItemSelectedMessageHandler::HandleReceivedSearchResultMenuItemSelectedMessage)
		{
			m_messageBus.Subscribe(m_handleSearchResultMenuItemSelectedMessageBinding);
		}

		SearchResultMenuItemSelectedMessageHandler::~SearchResultMenuItemSelectedMessageHandler()
		{
			m_messageBus.Unsubscribe(m_handleSearchResultMenuItemSelectedMessageBinding);
		}
	}
}
