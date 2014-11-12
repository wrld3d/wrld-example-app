// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IRepositoryModel.h"
#include "MenuItemModel.h"

namespace ExampleApp
{
namespace Menu
{
class IMenuModel : public Repository::IRepositoryModel<MenuItemModel>
{

};
}
}
