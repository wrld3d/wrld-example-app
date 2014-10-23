// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "SearchResultMenuViewController.h"
#include "Types.h"
#include "ISearchService.h"
#include "ICallback.h"
#include "SearchQuery.h"
#include "ICategorySearchRepository.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        class SearchResultMenuViewControllerInterop : private Eegeo::NonCopyable
        {
            SearchResultMenuViewController* m_pController;
            Search::ISearchService& m_searchService;
            CategorySearch::ICategorySearchRepository& m_categorySearchRepository;
            
            Eegeo::Helpers::ICallback1<const Search::SearchQuery&>* m_pSearchQueryIssuedCallback;
            Eegeo::Helpers::ICallback2<const Search::SearchQuery&, const std::vector<Search::SearchResultModel> &>* m_pSearchResultReceivedCallback;
            
            void HandleSearchQueryIssued(const Search::SearchQuery& query)
            {
                [m_pController updateHeaderInResponseToQueryIssued
                 :CategorySearch::GetPresentationStringForQuery(m_categorySearchRepository, query)];
            }
            
            void HandleSearchResultReceived(const Search::SearchQuery& query, const std::vector<Search::SearchResultModel>& results)
            {
                [m_pController updateHeaderInResponseToQueryResultsReceived
                 :CategorySearch::GetPresentationStringForQuery(m_categorySearchRepository, query)
                 :results.size()];
            }
            
        public:
            
            SearchResultMenuViewControllerInterop(SearchResultMenuViewController* pController,
                                                  Search::ISearchService& searchService,
                                                  CategorySearch::ICategorySearchRepository& categorySearchRepository)
            : m_pController(pController)
            , m_searchService(searchService)
            , m_categorySearchRepository(categorySearchRepository)
            , m_pSearchQueryIssuedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback1<SearchResultMenuViewControllerInterop, const Search::SearchQuery &>))(this, &SearchResultMenuViewControllerInterop::HandleSearchQueryIssued))
            , m_pSearchResultReceivedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<SearchResultMenuViewControllerInterop, const Search::SearchQuery&, const std::vector<Search::SearchResultModel> &>))(this, &SearchResultMenuViewControllerInterop::HandleSearchResultReceived))
            {
                m_searchService.InsertOnPerformedQueryCallback(*m_pSearchQueryIssuedCallback);
                m_searchService.InsertOnReceivedQueryResultsCallback(*m_pSearchResultReceivedCallback);
            }
            
            ~SearchResultMenuViewControllerInterop()
            {
                m_searchService.RemoveOnReceivedQueryResultsCallback(*m_pSearchResultReceivedCallback);
                m_searchService.RemoveOnPerformedQueryCallback(*m_pSearchQueryIssuedCallback);
                
                Eegeo_DELETE m_pSearchResultReceivedCallback;
                Eegeo_DELETE m_pSearchQueryIssuedCallback;
            }
        };
        
    }
}
