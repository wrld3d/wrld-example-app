// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMenuSearchQueryRemovedMessageHandler.h"

#include "IMenuViewModel.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            SearchResultMenuSearchQueryRemovedMessageHandler::SearchResultMenuSearchQueryRemovedMessageHandler(Menu::View::IMenuViewModel& searchMenuViewModel,
                                                                                                               ExampleAppMessaging::TMessageBus& messageBus)
            : m_searchMenuViewModel(searchMenuViewModel)
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
                // TODO: Clear search results from view
                m_searchMenuViewModel.Close();
            }
        }
    }
}
