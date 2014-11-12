// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "Menu.h"
#include "IPrimaryMenuViewModule.h"
#include "Rendering.h"
#include "Modality.h"

namespace ExampleApp
{
namespace PrimaryMenu
{
class PrimaryMenuViewModule: public IPrimaryMenuViewModule, private Eegeo::NonCopyable
{
private:
	MenuViewController* m_pMenuViewController;
	PrimaryMenuView* m_pView;

public:
	PrimaryMenuViewModule(Menu::IMenuModel& primaryMenuModel,
	                      Menu::IMenuViewModel& primaryMenuViewModel,
	                      const Eegeo::Rendering::ScreenProperties& screenProperties,
	                      Modality::IModalityModel& modalityModel);

	~PrimaryMenuViewModule();

	MenuViewController& GetPrimaryMenuViewController() const;

	PrimaryMenuView& GetPrimaryMenuView() const;
};
}
}
