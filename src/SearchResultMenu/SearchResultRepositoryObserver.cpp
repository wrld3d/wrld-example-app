// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultRepositoryObserver.h"

namespace ExampleApp
{
	namespace SearchResultMenu
	{
		SearchResultRepositoryObserver::SearchResultRepositoryObserver(
			Search::ISearchResultRepository& searchResultRepository,
			ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
			: m_searchResultRepository(searchResultRepository)
			, m_nativeToUiMessageBus(nativeToUiMessageBus)
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

		void SearchResultRepositoryObserver::HandleSearchResultAdded(Search::SearchResultModel*& pResult)
		{
			m_nativeToUiMessageBus.Publish(SearchResultAddedMessage(*pResult));
		}

		void SearchResultRepositoryObserver::HandleSearchResultRemoved(Search::SearchResultModel*& pResult)
		{
			m_nativeToUiMessageBus.Publish(SearchResultRemovedMessage(*pResult));
		}
	}
}
