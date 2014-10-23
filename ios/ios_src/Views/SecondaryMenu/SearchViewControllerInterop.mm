// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchViewControllerInterop.h"
#include "SearchViewController.h"
#include "ISearchService.h"
#include "IMenuViewModel.h"

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        SearchViewControllerInterop::SearchViewControllerInterop(SearchViewController* pInstance,
                                                                 ExampleApp::Menu::IMenuViewModel& menuViewModel,
                                                                 ExampleApp::Search::ISearchService& searchService)
        : m_pInstance(pInstance)
        , m_searchService(searchService)
        , m_menuViewModel(menuViewModel)
        , m_pPerformedQueryCallback(Eegeo_NEW((Eegeo::Helpers::TCallback1<SearchViewControllerInterop, const Search::SearchQuery&>))(this, &SearchViewControllerInterop::PerformedQueryCallback))
        , m_pReceivedQueryResponseCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<SearchViewControllerInterop, const Search::SearchQuery&, const std::vector<Search::SearchResultModel>&>))(this, &SearchViewControllerInterop::ReceivedQueryResponseCallback))
        , m_pMenuOpenStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<SearchViewControllerInterop, OpenableControlViewModel::IOpenableControlViewModel&, float>))(this, &SearchViewControllerInterop::HandleOpenStateChanged))
        {
            m_menuViewModel.InsertOpenStateChangedCallback(*m_pMenuOpenStateChangedCallback);
            m_searchService.InsertOnPerformedQueryCallback(*m_pPerformedQueryCallback);
            m_searchService.InsertOnReceivedQueryResultsCallback(*m_pReceivedQueryResponseCallback);
        }
        
        SearchViewControllerInterop::~SearchViewControllerInterop()
        {
            m_searchService.RemoveOnPerformedQueryCallback(*m_pPerformedQueryCallback);
            m_searchService.RemoveOnReceivedQueryResultsCallback(*m_pReceivedQueryResponseCallback);
            m_menuViewModel.RemoveOpenStateChangedCallback(*m_pMenuOpenStateChangedCallback);
            
            Eegeo_DELETE m_pPerformedQueryCallback;
            Eegeo_DELETE m_pReceivedQueryResponseCallback;
            Eegeo_DELETE m_pMenuOpenStateChangedCallback;
        }
        
        void SearchViewControllerInterop::PerformedQueryCallback(const Search::SearchQuery& query)
        {
            [m_pInstance disableEdit];
        }
        
        void SearchViewControllerInterop::ReceivedQueryResponseCallback(const Search::SearchQuery& query,
                                                                        const std::vector<Search::SearchResultModel>& results)
        {
            [m_pInstance enableEdit];
        }
        
        void SearchViewControllerInterop::HandleOpenStateChanged(OpenableControlViewModel::IOpenableControlViewModel& viewModel,
                                                                 float& openState)
        {
            if(openState != 1.f)
            {
                [m_pInstance removeSeachKeyboard];
            }
        }
    }
}
