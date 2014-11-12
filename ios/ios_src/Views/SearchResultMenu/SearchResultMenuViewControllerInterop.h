// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "SearchResultMenuViewController.h"
#include "Types.h"
#include "ISearchService.h"
#include "ICallback.h"
#include "SearchQuery.h"
#include "ICategorySearchRepository.h"
#include "NativeToUiMessageBus.h"
#include "SearchQueryPerformedMessage.h"
#include "SearchQueryResponseReceivedMessage.h"

namespace ExampleApp
{
namespace SearchResultMenu
{
class SearchResultMenuViewControllerInterop : private Eegeo::NonCopyable
{
	SearchResultMenuViewController* m_pController;
	CategorySearch::ICategorySearchRepository& m_categorySearchRepository;
	ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;

	Eegeo::Helpers::TCallback1<SearchResultMenuViewControllerInterop, const Search::SearchQueryPerformedMessage&> m_searchQueryIssuedCallback;
	Eegeo::Helpers::TCallback1<SearchResultMenuViewControllerInterop, const Search::SearchQueryResponseReceivedMessage&> m_searchResultReceivedCallback;

	void HandleSearchQueryIssued(const Search::SearchQueryPerformedMessage& message)
	{
		[m_pController updateHeaderInResponseToQueryIssued
		 :CategorySearch::GetPresentationStringForQuery(m_categorySearchRepository, message.Query())];
	}

	void HandleSearchResultReceived(const Search::SearchQueryResponseReceivedMessage& message)
	{
		[m_pController updateHeaderInResponseToQueryResultsReceived
		 :CategorySearch::GetPresentationStringForQuery(m_categorySearchRepository, message.GetQuery())
		 :message.GetResults().size()];
	}

public:

	SearchResultMenuViewControllerInterop(SearchResultMenuViewController* pController,
	                                      CategorySearch::ICategorySearchRepository& categorySearchRepository,
	                                      ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus
	                                     )
		: m_pController(pController)
		, m_nativeToUiMessageBus(nativeToUiMessageBus)
		, m_categorySearchRepository(categorySearchRepository)
		, m_searchResultReceivedCallback(this, &SearchResultMenuViewControllerInterop::HandleSearchResultReceived)
		, m_searchQueryIssuedCallback(this, &SearchResultMenuViewControllerInterop::HandleSearchQueryIssued)
	{
		m_nativeToUiMessageBus.Subscribe(m_searchResultReceivedCallback);
		m_nativeToUiMessageBus.Subscribe(m_searchQueryIssuedCallback);
	}

	~SearchResultMenuViewControllerInterop()
	{
		m_nativeToUiMessageBus.Unsubscribe(m_searchResultReceivedCallback);
		m_nativeToUiMessageBus.Unsubscribe(m_searchQueryIssuedCallback);
	}
};

}
}
