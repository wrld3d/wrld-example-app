// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "ICallback.h"
#include "ISearchQueryPerformer.h"
#include "SearchResultViewClearedMessage.h"
#include "Types.h"

namespace ExampleApp
{
    namespace SearchResultSection
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
