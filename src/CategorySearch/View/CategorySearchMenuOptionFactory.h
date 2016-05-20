// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMenuOption.h"
#include "CategorySearchModel.h"
#include "Search.h"
#include "Menu.h"
#include "BidirectionalBus.h"
#include "IMenuReactionModel.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        namespace View
        {
            class CategorySearchMenuOptionFactory
            {
                CategorySearchMenuOptionFactory();
                ~CategorySearchMenuOptionFactory();
            public:
                static Menu::View::IMenuOption* CreateCategorySearchMenuOption(CategorySearchModel model,
                                                                               Menu::View::IMenuViewModel& menuViewModel,
                                                                               ExampleAppMessaging::TMessageBus& messageBus,
                                                                               const Menu::View::IMenuReactionModel& menuReaction);
            };
        }
    }
}
