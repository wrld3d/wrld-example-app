// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IRepositoryModel.h"
#include "MenuItemModel.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            class IMenuModel : public Repository::IRepositoryModel<MenuItemModel>
            {

            };
        }
    }
}
