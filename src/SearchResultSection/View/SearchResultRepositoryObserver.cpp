// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultRepositoryObserver.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace View
        {
            SearchResultRepositoryObserver::SearchResultRepositoryObserver(Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                                                           ExampleAppMessaging::TMessageBus& messageBus)
            : m_searchResultRepository(searchResultRepository)
            , m_messageBus(messageBus)
            , m_addedCallback(this, &SearchResultRepositoryObserver::HandleSearchResultAdded)
            , m_removedCallback(this, &SearchResultRepositoryObserver::HandleSearchResultRemoved)
            {
                m_searchResultRepository.InsertItemAddedCallback(m_addedCallback);
                m_searchResultRepository.InsertItemRemovedCallback(m_removedCallback);
            }

            SearchResultRepositoryObserver::~SearchResultRepositoryObserver()
            {
                m_searchResultRepository.RemoveItemAddedCallback(m_addedCallback);
                m_searchResultRepository.RemoveItemRemovedCallback(m_removedCallback);
            }

            void SearchResultRepositoryObserver::HandleSearchResultAdded(Search::SdkModel::SearchResultModel*& pResult)
            {
                m_messageBus.Publish(SearchResultAddedMessage(*pResult));
            }

            void SearchResultRepositoryObserver::HandleSearchResultRemoved(Search::SdkModel::SearchResultModel*& pResult)
            {
                m_messageBus.Publish(SearchResultRemovedMessage(*pResult));
            }
        }
    }
}
