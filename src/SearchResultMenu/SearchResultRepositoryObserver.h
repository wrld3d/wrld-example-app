// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "ISearchResultRepository.h"
#include "NativeToUiMessageBus.h"
#include "ICallback.h"
#include "SearchResultAddedMessage.h"
#include "SearchResultRemovedMessage.h"

namespace ExampleApp
{
namespace SearchResultMenu
{
class SearchResultRepositoryObserver : private Eegeo::NonCopyable
{
private:
	Search::ISearchResultRepository& m_searchResultRepository;
	ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;

	Eegeo::Helpers::TCallback1<SearchResultRepositoryObserver, Search::SearchResultModel*> m_addedCallback;
	Eegeo::Helpers::TCallback1<SearchResultRepositoryObserver, Search::SearchResultModel*> m_removedCallback;

	void HandleSearchResultAdded(Search::SearchResultModel*& pResult)
	{
		m_nativeToUiMessageBus.Publish(SearchResultAddedMessage(*pResult));
	}

	void HandleSearchResultRemoved(Search::SearchResultModel*& pResult)
	{
		m_nativeToUiMessageBus.Publish(SearchResultRemovedMessage(*pResult));
	}

public:
	SearchResultRepositoryObserver(
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

	~SearchResultRepositoryObserver()
	{
		m_searchResultRepository.RemoveItemAddedCallback(m_addedCallback);
		m_searchResultRepository.RemoveItemRemovedCallback(m_removedCallback);
	}
};
}
}
