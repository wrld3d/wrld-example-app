// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include <vector>

#include "AndroidNativeState.h"
#include "Types.h"
#include "MenuViewIncludes.h"
#include "MenuViewController.h"
#include "ICallback.h"
#include "Menu.h"
#include "IMenuViewModel.h"
#include "ScreenControlViewModelIncludes.h"
#include "OpenableControlViewModelIncludes.h"
#include "Search.h"
#include "SearchQuery.h"
#include "CategorySearch.h"
#include "SearchResultMenu.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
		class SearchMenuViewController : public Menu::MenuViewController
		{
            Search::ISearchService& m_searchService;
            Eegeo::Helpers::ICallback1<const Search::SearchQuery&>* m_pSearchResultQueryIssuedCallback;
            Eegeo::Helpers::ICallback2<const Search::SearchQuery&, const std::vector<Search::SearchResultModel> &>* m_pSearchResultReceivedCallback;
            Search::ISearchQueryPerformer& m_queryPerformer;
            CategorySearch::ICategorySearchRepository& m_categorySearchRepository;
            SearchResultMenu::ISearchResultMenuViewModel& m_searchResultMenuViewModel;

			bool TryBeginDrag();

			void HandleViewClicked();

			void HandleSearchQueryIssued(const Search::SearchQuery& query);

			void HandleSearchResultReceived(const Search::SearchQuery& query, const std::vector<Search::SearchResultModel>& results);

            std::string GetHeaderTextForQuery(const Search::SearchQuery& query);

        	void RefreshViewHeader(const Search::SearchQuery& headerText, bool queryPending, int numResult);

		public:
		    SearchMenuViewController(
				const std::string& viewClassName,
				AndroidNativeState& nativeState,
				Menu::IMenuModel& menuModel,
				Menu::IMenuViewModel& menuViewModel,
				Search::ISearchService& searchService,
                Search::ISearchQueryPerformer& queryPerformer,
	            CategorySearch::ICategorySearchRepository& categorySearchRepository,
	            SearchResultMenu::ISearchResultMenuViewModel& searchResultMenuViewModel
			);

			~SearchMenuViewController();

			void HandleClosed();
		};
	}
}

