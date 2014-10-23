// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include "AndroidNativeState.h"
#include "Types.h"
#include "Menu.h"
#include "PrimaryMenu.h"
#include "MenuViewIncludes.h"
#include "IMenuViewModule.h"
#include "Search.h"
#include "CategorySearch.h"
#include "SearchResultMenu.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        class SearchMenuViewModule: public Menu::IMenuViewModule, private Eegeo::NonCopyable
        {
        private:
        	Menu::IMenuViewController* m_pMenuViewController;
            
        public:
        	SearchMenuViewModule(
        		const std::string& viewName,
            	AndroidNativeState& nativeState,
        		Menu::IMenuModel& menuModelModel,
        		Menu::IMenuViewModel& menuViewModel,
        		Search::ISearchQueryPerformer& searchQueryPerformer,
        		Search::ISearchService& searchService,
                CategorySearch::ICategorySearchRepository& categorySearchRepository,
	            SearchResultMenu::ISearchResultMenuViewModel& searchResultMenuViewModel
            );
            
            ~SearchMenuViewModule();
            
            Menu::IMenuViewController& GetMenuViewController() const;
        };
    }
}
