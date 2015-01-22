// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "SearchQueryPerformedMessage.h"
#include "ISearchResultMenuViewModel.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            class SearchResultMenuSearchQueryPerformedMessageHandler : private Eegeo::NonCopyable
            {
                ISearchResultMenuViewModel& m_searchResultMenuViewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<SearchResultMenuSearchQueryPerformedMessageHandler, const Search::SearchQueryPerformedMessage&> m_handlerBinding;

                void OnSearchQueryPerformedMessage(const Search::SearchQueryPerformedMessage& message);

            public:
                SearchResultMenuSearchQueryPerformedMessageHandler(
                    ISearchResultMenuViewModel& searchResultMenuViewModel,
                    ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchResultMenuSearchQueryPerformedMessageHandler();
            };
        }
    }
}
