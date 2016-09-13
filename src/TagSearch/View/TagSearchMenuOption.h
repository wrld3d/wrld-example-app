// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMenuOption.h"
#include "TagSearchModel.h"
#include "Search.h"
#include "Menu.h"
#include "BidirectionalBus.h"
#include "IMenuReactionModel.h"
#include "MenuOptionsModel.h"
#include "MenuModel.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace View
        {
            class TagSearchMenuModel : public Menu::View::MenuModel
            {
            };
            
            class TagSearchMenuOptionsModel : public Menu::View::MenuOptionsModel
            {
            public:
                TagSearchMenuOptionsModel(const std::shared_ptr<TagSearchMenuModel>& settingsMenuModel) : Menu::View::MenuOptionsModel(*settingsMenuModel)
                {
                }
            };
            
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
