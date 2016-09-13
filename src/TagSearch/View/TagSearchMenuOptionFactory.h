// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMenuOption.h"
#include "TagSearchModel.h"
#include "Search.h"
#include "Menu.h"
#include "BidirectionalBus.h"
#include "IMenuReactionModel.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace View
        {
            class TagSearchMenuOptionFactory
            {
            private:
                TagSearchMenuOptionFactory();
                ~TagSearchMenuOptionFactory();

            public:
                static Menu::View::IMenuOption* CreateTagSearchMenuOption(
                        TagSearchModel model,
                        Menu::View::IMenuViewModel& menuViewModel,
                        ExampleAppMessaging::TMessageBus& messageBus,
                        const Menu::View::IMenuReactionModel& menuReaction);
            };
        }
    }
}
