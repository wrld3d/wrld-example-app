// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "Types.h"
#include "TagSearch.h"
#include "Menu.h"
#include "BidirectionalBus.h"
#include "IMenuReactionModel.h"
#include "TagSearchMenuOption.h"
#include "SearchMenuOptions.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace View
        {
            class TagSearchSectionController : private Eegeo::NonCopyable
            {
            private:
                const std::shared_ptr<Menu::View::IMenuOptionsModel> m_menuOptionsModel;
                const std::shared_ptr<Menu::View::IMenuViewModel> m_menuViewModel;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                const std::shared_ptr<const Menu::View::IMenuReactionModel> m_menuReaction;

                Eegeo::Helpers::TCallback1<TagSearchSectionController, const TagSearch::TagSearchAddedMessage&> m_tagSearchAddedMessageHandler;
                Eegeo::Helpers::TCallback1<TagSearchSectionController, const TagSearch::TagSearchRemovedMessage&> m_tagSearchRemovedMessageHandler;

                void OnTagSearchAddedMessage(const TagSearch::TagSearchAddedMessage& message);
                void OnTagSearchRemovedMessage(const TagSearch::TagSearchRemovedMessage& message);
                            
            public:
                TagSearchSectionController(
                                           const std::shared_ptr<TagSearch::View::TagSearchMenuOptionsModel>& menuOptionsModel,
                                           const std::shared_ptr<SearchMenu::View::SearchMenuViewModel>& menuViewModel,
                                           const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                           const std::shared_ptr<Menu::View::IMenuReactionModel>& menuReaction);

                ~TagSearchSectionController();
            };
        }
    }
}
