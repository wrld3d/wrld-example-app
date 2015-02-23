// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMenuOption.h"
#include "CategorySearchModel.h"
#include "Search.h"
#include "Menu.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        namespace View
        {
            class CategorySearchMenuOption : public Menu::View::IMenuOption
            {
                CategorySearchModel m_model;
                Menu::View::IMenuViewModel& m_menuViewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;

            public:
                CategorySearchMenuOption(CategorySearchModel model,
                                         Menu::View::IMenuViewModel& menuViewModel,
                                         ExampleAppMessaging::TMessageBus& messageBus);

                ~CategorySearchMenuOption();

                void Select();
            };
        }
    }
}
