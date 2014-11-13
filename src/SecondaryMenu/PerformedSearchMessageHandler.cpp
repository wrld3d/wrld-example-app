// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PerformedSearchMessageHandler.h"

namespace ExampleApp
{
	namespace SecondaryMenu
	{
		PerformedSearchMessageHandler::PerformedSearchMessageHandler(
			Search::ISearchQueryPerformer& searchQueryPerformer,
			ExampleAppMessaging::UiToNativeMessageBus& messageBus)
			: m_searchQueryPerformer(searchQueryPerformer)
			, m_messageBus(messageBus)
			, m_handlePerformedSearchMessageBinding(this, &PerformedSearchMessageHandler::HandleReceivedPerformedSearchMessage)
		{
			m_messageBus.Subscribe(m_handlePerformedSearchMessageBinding);
		}

		PerformedSearchMessageHandler::~PerformedSearchMessageHandler()
		{
			m_messageBus.Unsubscribe(m_handlePerformedSearchMessageBinding);
		}

		void PerformedSearchMessageHandler::HandleReceivedPerformedSearchMessage(const PerformedSearchMessage& message)
		{
			m_searchQueryPerformer.PerformSearchQuery(message.SearchQuery(), message.IsCategory());
		}
	}
}
