// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "ICallback.h"
#include "ISearchQueryPerformer.h"
#include "SearchResultViewClearedMessage.h"
#include "Types.h"

#include <memory>

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace SdkModel
        {
            class SearchResultViewClearedObserver : private Eegeo::NonCopyable
            {
            private:
                const std::shared_ptr<Search::SdkModel::ISearchQueryPerformer> m_searchQueryPerformer;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                Eegeo::Helpers::TCallback1<SearchResultViewClearedObserver, const SearchResultViewClearedMessage&> m_handler;

                void OnSearchResultViewClearedMessage(const SearchResultViewClearedMessage& message);

            public:
                SearchResultViewClearedObserver(const std::shared_ptr<Search::SdkModel::ISearchQueryPerformer>& searchQueryPerformer,
                                                const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);

                ~SearchResultViewClearedObserver();
            };
        }
    }
}
