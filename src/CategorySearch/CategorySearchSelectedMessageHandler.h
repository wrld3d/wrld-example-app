// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "UiToNativeMessageBus.h"
#include "ISearchQueryPerformer.h"
#include "ICallback.h"

namespace ExampleApp
{
	namespace CategorySearch
	{
		class CategorySearchSelectedMessageHandler : private Eegeo::NonCopyable
		{
			Search::ISearchQueryPerformer& m_searchQueryPerformer;
			ExampleAppMessaging::UiToNativeMessageBus& m_messageBus;
			Eegeo::Helpers::TCallback1<CategorySearchSelectedMessageHandler, const CategorySearchSelectedMessage&> m_handlerBinding;

			void HandleReceivedCategorySearchSelectedMessage(const CategorySearchSelectedMessage& message)
			{
				m_searchQueryPerformer.PerformSearchQuery(message.Category(), true);
			}

		public:
			CategorySearchSelectedMessageHandler(
			    Search::ISearchQueryPerformer& searchQueryPerformer,
			    ExampleAppMessaging::UiToNativeMessageBus& messageBus)
				: m_searchQueryPerformer(searchQueryPerformer)
				, m_messageBus(messageBus)
				, m_handlerBinding(this, &CategorySearchSelectedMessageHandler::HandleReceivedCategorySearchSelectedMessage)
			{
				m_messageBus.Subscribe(m_handlerBinding);
			}

			~CategorySearchSelectedMessageHandler()
			{
				m_messageBus.Unsubscribe(m_handlerBinding);
			}
		};
	}
}
