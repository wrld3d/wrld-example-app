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
            class TagSearchMenuOption : public Menu::View::IMenuOption
            {
                TagSearchModel m_model;
                Menu::View::IMenuViewModel& m_menuViewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                const Menu::View::IMenuReactionModel& m_menuReaction;

            public:
                TagSearchMenuOption(
                        TagSearchModel model,
                        Menu::View::IMenuViewModel& menuViewModel,
                        ExampleAppMessaging::TMessageBus& messageBus,
                        const Menu::View::IMenuReactionModel& menuReaction);

                ~TagSearchMenuOption();

                void Select();
            };
        }
    }
}
