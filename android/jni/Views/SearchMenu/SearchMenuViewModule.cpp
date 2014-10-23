// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidNativeState.h"
#include "Menu.h"
#include "SearchMenuViewModule.h"
#include "SearchMenuViewController.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
    	SearchMenuViewModule::SearchMenuViewModule(
    		const std::string& viewName,
			AndroidNativeState& nativeState,
			Menu::IMenuModel& menuModel,
			Menu::IMenuViewModel& menuViewModel,
    		Search::ISearchQueryPerformer& searchQueryPerformer,
    		Search::ISearchService& searchService,
            CategorySearch::ICategorySearchRepository& categorySearchRepository,
            SearchResultMenu::ISearchResultMenuViewModel& searchResultMenuViewModel
		)
        {
            m_pMenuViewController = Eegeo_NEW(SearchMenuViewController)(
				viewName,
				nativeState,
				menuModel,
				menuViewModel,
				searchService,
				searchQueryPerformer,
				categorySearchRepository,
				searchResultMenuViewModel
			);
        }
        
    	SearchMenuViewModule::~SearchMenuViewModule()
        {
            Eegeo_DELETE m_pMenuViewController;
        }
        
        Menu::IMenuViewController& SearchMenuViewModule::GetMenuViewController() const
        {
            return *m_pMenuViewController;
        }
    }
}
