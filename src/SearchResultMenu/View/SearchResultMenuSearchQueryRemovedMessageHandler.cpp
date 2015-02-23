// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMenuSearchQueryRemovedMessageHandler.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            SearchResultMenuSearchQueryRemovedMessageHandler::SearchResultMenuSearchQueryRemovedMessageHandler(
                ISearchResultMenuViewModel& searchResultMenuViewModel,
                ExampleAppMessaging::TMessageBus& messageBus)
                : m_searchResultMenuViewModel(searchResultMenuViewModel)
                , m_messageBus(messageBus)
                , m_handlerBinding(this, &SearchResultMenuSearchQueryRemovedMessageHandler::OnSearchQueryRemovedMessage)
            {
                m_messageBus.SubscribeUi(m_handlerBinding);
            }

            SearchResultMenuSearchQueryRemovedMessageHandler::~SearchResultMenuSearchQueryRemovedMessageHandler()
            {
                m_messageBus.UnsubscribeUi(m_handlerBinding);
            }

            void SearchResultMenuSearchQueryRemovedMessageHandler::OnSearchQueryRemovedMessage(const Search::SearchQueryRemovedMessage& message)
            {
                m_searchResultMenuViewModel.SetHasSearchQuery(false);
            }
        }
    }
}
