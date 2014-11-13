// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CategorySearchSelectedMessageHandler.h"

namespace ExampleApp
{
	namespace CategorySearch
	{
		void CategorySearchSelectedMessageHandler::HandleReceivedCategorySearchSelectedMessage(const CategorySearchSelectedMessage& message)
		{
			m_searchQueryPerformer.PerformSearchQuery(message.Category(), true);
		}

		CategorySearchSelectedMessageHandler::CategorySearchSelectedMessageHandler(
			Search::ISearchQueryPerformer& searchQueryPerformer,
			ExampleAppMessaging::UiToNativeMessageBus& messageBus)
			: m_searchQueryPerformer(searchQueryPerformer)
			, m_messageBus(messageBus)
			, m_handlerBinding(this, &CategorySearchSelectedMessageHandler::HandleReceivedCategorySearchSelectedMessage)
		{
			m_messageBus.Subscribe(m_handlerBinding);
		}

		CategorySearchSelectedMessageHandler::~CategorySearchSelectedMessageHandler()
		{
			m_messageBus.Unsubscribe(m_handlerBinding);
		}
	}
}
