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



namespace ExampleApp
{
    namespace SecondaryMenu
    {
		class SecondaryMenuViewController : public Menu::MenuViewController
		{
            Search::ISearchService& m_searchService;
			Search::ISearchQueryPerformer& m_searchQueryPerformer;

			Eegeo::Helpers::ICallback1<const Search::SearchQuery&>* m_pPerformedQueryCallback;
			Eegeo::Helpers::ICallback2<const Search::SearchQuery&, const std::vector<Search::SearchResultModel>&>* m_pReceivedQueryResponseCallback;
			Eegeo::Helpers::ICallback2<OpenableControlViewModel::IOpenableControlViewModel&, float>* m_pMenuOpenStateChangedCallback;

		public:
		    SecondaryMenuViewController(
		    		const std::string& viewClassName,
					AndroidNativeState& nativeState,
					Menu::IMenuModel& menuModel,
					Menu::IMenuViewModel& menuViewModel,
					Search::ISearchService& searchService,
					Search::ISearchQueryPerformer& searchQueryPerformer
			);

			~SecondaryMenuViewController();

			void HandleSearch(const std::string& query);

		private:

            void PerformedQueryCallback(const Search::SearchQuery& query);

            void ReceivedQueryResponseCallback(const Search::SearchQuery& query, const std::vector<Search::SearchResultModel>& results);

            void HandleOpenStateChanged(OpenableControlViewModel::IOpenableControlViewModel& viewModel, float& openState);

		};
	}
}
