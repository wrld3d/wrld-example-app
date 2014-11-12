// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IScreenControlViewModel.h"
#include "IOpenableControlViewModel.h"
#include "IMenuSectionsViewModel.h"
#include "Menu.h"

namespace ExampleApp
{
namespace Menu
{
class IMenuViewModel
	: public ScreenControlViewModel::IScreenControlViewModel
	, public OpenableControlViewModel::IOpenableControlViewModel
	, public IMenuSectionsViewModel
{
public:
	virtual ~IMenuViewModel() { }
};
}
}
