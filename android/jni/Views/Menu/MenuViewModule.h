// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include "AndroidNativeState.h"
#include "Types.h"
#include "Menu.h"
#include "PrimaryMenu.h"
#include "MenuViewIncludes.h"
#include "IMenuViewModule.h"

namespace ExampleApp
{
namespace Menu
{
class MenuViewModule: public IMenuViewModule, private Eegeo::NonCopyable
{
private:
	MenuViewController* m_pMenuViewController;

public:
	MenuViewModule(
	    const std::string& viewName,
	    AndroidNativeState& nativeState,
	    Menu::IMenuModel& menuModelModel,
	    Menu::IMenuViewModel& menuViewModel
	);

	~MenuViewModule();

	IMenuViewController& GetMenuViewController() const;
};
}
}
