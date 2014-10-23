// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidNativeState.h"
#include "Menu.h"
#include "SecondaryMenuViewModule.h"
#include "SecondaryMenuViewController.h"

namespace ExampleApp
{
    namespace SecondaryMenu
    {
    	SecondaryMenuViewModule::SecondaryMenuViewModule(
    		const std::string& viewName,
			AndroidNativeState& nativeState,
			Menu::IMenuModel& menuModel,
			Menu::IMenuViewModel& menuViewModel,
			Search::ISearchService& searchService,
			Search::ISearchQueryPerformer& searchQueryPerformer
		)
        {
            m_pMenuViewController = Eegeo_NEW(SecondaryMenuViewController)(
				viewName,
				nativeState,
				menuModel,
				menuViewModel,
				searchService,
				searchQueryPerformer
			);
        }
        
    	SecondaryMenuViewModule::~SecondaryMenuViewModule()
        {
            Eegeo_DELETE m_pMenuViewController;
        }
        
        Menu::IMenuViewController& SecondaryMenuViewModule::GetMenuViewController() const
        {
            return *m_pMenuViewController;
        }
    }
}
