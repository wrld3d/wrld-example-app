// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PerformedSearchMessageHandler.h"

namespace ExampleApp
{
	namespace SecondaryMenu
	{
		PerformedSearchMessageHandler::PerformedSearchMessageHandler(
			Search::ISearchQueryPerformer& searchQueryPerformer,
			ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
			: m_searchQueryPerformer(searchQueryPerformer)
			, m_uiToNativeMessageBus(uiToNativeMessageBus)
			, m_handlePerformedSearchMessageBinding(this, &PerformedSearchMessageHandler::HandleReceivedPerformedSearchMessage)
		{
			m_uiToNativeMessageBus.Subscribe(m_handlePerformedSearchMessageBinding);
		}

		PerformedSearchMessageHandler::~PerformedSearchMessageHandler()
		{
			m_uiToNativeMessageBus.Unsubscribe(m_handlePerformedSearchMessageBinding);
		}

		void PerformedSearchMessageHandler::HandleReceivedPerformedSearchMessage(const PerformedSearchMessage& message)
		{
			m_searchQueryPerformer.PerformSearchQuery(message.SearchQuery(), message.IsCategory());
		}
	}
}
