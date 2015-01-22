// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "SearchQueryRemovedMessage.h"
#include "ISearchResultMenuViewModel.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            class SearchResultMenuSearchQueryRemovedMessageHandler : private Eegeo::NonCopyable
            {
                ISearchResultMenuViewModel& m_searchResultMenuViewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<SearchResultMenuSearchQueryRemovedMessageHandler, const Search::SearchQueryRemovedMessage&> m_handlerBinding;

                void OnSearchQueryRemovedMessage(const Search::SearchQueryRemovedMessage& message);

            public:
                SearchResultMenuSearchQueryRemovedMessageHandler(
                    ISearchResultMenuViewModel& searchResultMenuViewModel,
                    ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchResultMenuSearchQueryRemovedMessageHandler();
            };
        }
    }
}
