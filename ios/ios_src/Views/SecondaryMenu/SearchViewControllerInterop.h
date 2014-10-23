// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "Search.h"
#include "ICallback.h"
#include "IOpenableControlViewModel.h"
#include "Menu.h"

@class SearchViewController;

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        class SearchViewControllerInterop : private Eegeo::NonCopyable
        {
            SearchViewController* m_pInstance;
            ExampleApp::Search::ISearchService& m_searchService;
            ExampleApp::Menu::IMenuViewModel& m_menuViewModel;
            
            Eegeo::Helpers::ICallback1<const Search::SearchQuery&>* m_pPerformedQueryCallback;
            Eegeo::Helpers::ICallback2<const Search::SearchQuery&, const std::vector<Search::SearchResultModel>&>* m_pReceivedQueryResponseCallback;
            Eegeo::Helpers::ICallback2<OpenableControlViewModel::IOpenableControlViewModel&, float>* m_pMenuOpenStateChangedCallback;
            
            void PerformedQueryCallback(const Search::SearchQuery& query);
            
            void ReceivedQueryResponseCallback(const Search::SearchQuery& query, const std::vector<Search::SearchResultModel>& results);
            
            void HandleOpenStateChanged(OpenableControlViewModel::IOpenableControlViewModel& viewModel, float& openState);
            
        public:
            SearchViewControllerInterop(SearchViewController* pInstance,
                                        ExampleApp::Menu::IMenuViewModel& menuViewModel,
                                        ExampleApp::Search::ISearchService& searchService);
            
            ~SearchViewControllerInterop();
        };
    }
}
