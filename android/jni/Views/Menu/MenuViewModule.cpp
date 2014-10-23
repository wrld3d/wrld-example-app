// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidNativeState.h"
#include "Menu.h"
#include "MenuViewModule.h"
#include "MenuViewController.h"

namespace ExampleApp
{
    namespace Menu
    {
    	MenuViewModule::MenuViewModule(
    		const std::string& viewName,
			AndroidNativeState& nativeState,
			Menu::IMenuModel& menuModel,
			Menu::IMenuViewModel& menuViewModel
		)
        {
            m_pMenuViewController = Eegeo_NEW(MenuViewController)(viewName, nativeState, menuModel, menuViewModel);
        }
        
    	MenuViewModule::~MenuViewModule()
        {
            Eegeo_DELETE m_pMenuViewController;
        }
        
        IMenuViewController& MenuViewModule::GetMenuViewController() const
        {
            return *m_pMenuViewController;
        }
    }
}
