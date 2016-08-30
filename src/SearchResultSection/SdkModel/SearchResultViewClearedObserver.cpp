// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultViewClearedObserver.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace SdkModel
        {
            SearchResultViewClearedObserver::SearchResultViewClearedObserver(const std::shared_ptr<Search::SdkModel::ISearchQueryPerformer>& searchQueryPerformer,
                                                                             const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus)
            : m_searchQueryPerformer(searchQueryPerformer)
            , m_messageBus(messageBus)
            , m_handler(this, &SearchResultViewClearedObserver::OnSearchResultViewClearedMessage)
            {
                m_messageBus->SubscribeNative(m_handler);
            }

            SearchResultViewClearedObserver::~SearchResultViewClearedObserver()
            {
                m_messageBus->UnsubscribeNative(m_handler);
            }
            
            void SearchResultViewClearedObserver::OnSearchResultViewClearedMessage(const SearchResultViewClearedMessage& message)
            {
                m_searchQueryPerformer->RemoveSearchQueryResults();
            }
        }
    }
}
