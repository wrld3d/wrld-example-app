// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ISearchQueryPerformer.h"
#include "BidirectionalBus.h"
#include "SearchResultViewClearedMessage.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace SdkModel
        {
            class SearchResultViewClearedObserver : private Eegeo::NonCopyable
            {
            private:
                Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<SearchResultViewClearedObserver, const SearchResultViewClearedMessage&> m_handler;

                void OnSearchResultViewClearedMessage(const SearchResultViewClearedMessage& message);

            public:
                SearchResultViewClearedObserver(Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchResultViewClearedObserver();
            };
        }
    }
}
