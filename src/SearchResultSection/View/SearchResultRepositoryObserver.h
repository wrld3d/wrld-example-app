// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "ICallback.h"
#include "ISearchResultRepository.h"
#include "SearchResultAddedMessage.h"
#include "SearchResultRemovedMessage.h"
#include "Types.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace View
        {
            class SearchResultRepositoryObserver : private Eegeo::NonCopyable
            {
            private:
                const std::shared_ptr<Search::SdkModel::ISearchResultRepository> m_searchResultRepository;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;

                Eegeo::Helpers::TCallback1<SearchResultRepositoryObserver, Search::SdkModel::SearchResultModel*> m_addedCallback;
                Eegeo::Helpers::TCallback1<SearchResultRepositoryObserver, Search::SdkModel::SearchResultModel*> m_removedCallback;

                void HandleSearchResultAdded(Search::SdkModel::SearchResultModel*& pResult);

                void HandleSearchResultRemoved(Search::SdkModel::SearchResultModel*& pResult);

            public:
                SearchResultRepositoryObserver(const std::shared_ptr<Search::SdkModel::ISearchResultRepository>& searchResultRepository,
                                               const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);

                ~SearchResultRepositoryObserver();
            };
        }
    }
}
