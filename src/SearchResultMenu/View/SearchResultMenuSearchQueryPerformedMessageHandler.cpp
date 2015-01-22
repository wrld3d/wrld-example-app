// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMenuSearchQueryPerformedMessageHandler.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            SearchResultMenuSearchQueryPerformedMessageHandler::SearchResultMenuSearchQueryPerformedMessageHandler(
                ISearchResultMenuViewModel& searchResultMenuViewModel,
                ExampleAppMessaging::TMessageBus& messageBus)
                : m_searchResultMenuViewModel(searchResultMenuViewModel)
                , m_messageBus(messageBus)
                , m_handlerBinding(this, &SearchResultMenuSearchQueryPerformedMessageHandler::OnSearchQueryPerformedMessage)
            {
                m_messageBus.SubscribeUi(m_handlerBinding);
            }

            SearchResultMenuSearchQueryPerformedMessageHandler::~SearchResultMenuSearchQueryPerformedMessageHandler()
            {
                m_messageBus.UnsubscribeUi(m_handlerBinding);
            }

            void SearchResultMenuSearchQueryPerformedMessageHandler::OnSearchQueryPerformedMessage(const Search::SearchQueryPerformedMessage& message)
            {
                m_searchResultMenuViewModel.SetHasSearchQuery(true);
            }
        }
    }
}
