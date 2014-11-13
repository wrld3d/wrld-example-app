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

			void HandleReceivedPerformedSearchMessage(const PerformedSearchMessage& message);

		public:
			PerformedSearchMessageHandler(
			    Search::ISearchQueryPerformer& searchQueryPerformer,
			    ExampleAppMessaging::UiToNativeMessageBus& messageBus);

			~PerformedSearchMessageHandler();
		};
	}
}
