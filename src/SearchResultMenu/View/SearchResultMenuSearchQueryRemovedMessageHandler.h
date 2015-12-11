// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "ICallback.h"
#include "SearchQueryRemovedMessage.h"
#include "Menu.h"
#include "Types.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            class SearchResultMenuSearchQueryRemovedMessageHandler : private Eegeo::NonCopyable
            {
                Menu::View::IMenuViewModel& m_searchMenuViewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<SearchResultMenuSearchQueryRemovedMessageHandler, const Search::SearchQueryRemovedMessage&> m_handlerBinding;

                void OnSearchQueryRemovedMessage(const Search::SearchQueryRemovedMessage& message);

            public:
                SearchResultMenuSearchQueryRemovedMessageHandler(Menu::View::IMenuViewModel& searchMenuViewModel,
                                                                 ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchResultMenuSearchQueryRemovedMessageHandler();
            };
        }
    }
}
