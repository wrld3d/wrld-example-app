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
			ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
			: m_searchQueryPerformer(searchQueryPerformer)
			, m_uiToNativeMessageBus(uiToNativeMessageBus)
			, m_handlerBinding(this, &CategorySearchSelectedMessageHandler::HandleReceivedCategorySearchSelectedMessage)
		{
			m_uiToNativeMessageBus.Subscribe(m_handlerBinding);
		}

		CategorySearchSelectedMessageHandler::~CategorySearchSelectedMessageHandler()
		{
			m_uiToNativeMessageBus.Unsubscribe(m_handlerBinding);
		}
	}
}
