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
#include "ICallback.h"
#include "UiToNativeMessageBus.h"
#include "NativeToUiMessageBus.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
		class SearchMenuViewController : public Menu::MenuViewController
		{
            Eegeo::Helpers::TCallback1<SearchMenuViewController, const Search::SearchQueryPerformedMessage&> m_searchQueryIssuedCallback;
            Eegeo::Helpers::TCallback1<SearchMenuViewController, const Search::SearchQueryResponseReceivedMessage&> m_searchResultReceivedCallback;

            ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
            ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;

            CategorySearch::ICategorySearchRepository& m_categorySearchRepository;
            SearchResultMenu::ISearchResultMenuViewModel& m_searchResultMenuViewModel;

			bool TryBeginDrag();

			void HandleViewClicked();

            void HandleSearchQueryIssued(const Search::SearchQueryPerformedMessage& message);

            void HandleSearchResultReceived(const Search::SearchQueryResponseReceivedMessage& message);

            std::string GetHeaderTextForQuery(const Search::SearchQuery& query);

        	void RefreshViewHeader(const Search::SearchQuery& headerText, bool queryPending, int numResult);

		public:
		    SearchMenuViewController(
				const std::string& viewClassName,
				AndroidNativeState& nativeState,
				Menu::IMenuModel& menuModel,
				Menu::IMenuViewModel& menuViewModel,
	            CategorySearch::ICategorySearchRepository& categorySearchRepository,
	            SearchResultMenu::ISearchResultMenuViewModel& searchResultMenuViewModel,
	            ExampleApp::ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
	            ExampleApp::ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus
			);

			~SearchMenuViewController();

			void HandleClosed();
		};
	}
}

