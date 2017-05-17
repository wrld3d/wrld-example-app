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
                ExampleAppMessaging::TMessageBus& m_messageBus;

            public:
                TagSearchMenuOption(
                        TagSearchModel model,
                        ExampleAppMessaging::TMessageBus& messageBus);

                ~TagSearchMenuOption();

                void Select();
            };
        }
    }
}
