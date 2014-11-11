// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "UiToNativeMessageBus.h"
#include "ICallback.h"
#include "PerformedSearchMessage.h"
#include "ISearchQueryPerformer.h"

namespace ExampleApp
{
	namespace SecondaryMenu
	{
		class PerformedSearchMessageHandler : private Eegeo::NonCopyable
		{
			Search::ISearchQueryPerformer& m_searchQueryPerformer;
			ExampleAppMessaging::UiToNativeMessageBus& m_messageBus;
			Eegeo::Helpers::TCallback1<PerformedSearchMessageHandler, const PerformedSearchMessage&> m_handlePerformedSearchMessageBinding;

			void HandleReceivedPerformedSearchMessage(const PerformedSearchMessage& message)
			{
				m_searchQueryPerformer.PerformSearchQuery(message.SearchQuery(), message.IsCategory());
			}

		public:
			PerformedSearchMessageHandler(
				Search::ISearchQueryPerformer& searchQueryPerformer,
				ExampleAppMessaging::UiToNativeMessageBus& messageBus)
			: m_searchQueryPerformer(searchQueryPerformer)
			, m_messageBus(messageBus)
			, m_handlePerformedSearchMessageBinding(this, &PerformedSearchMessageHandler::HandleReceivedPerformedSearchMessage)
			{
				m_messageBus.Subscribe(m_handlePerformedSearchMessageBinding);
			}

			~PerformedSearchMessageHandler()
			{
				m_messageBus.Unsubscribe(m_handlePerformedSearchMessageBinding);
			}
		};
	}
}
