// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "Types.h"
#include "TagSearch.h"
#include "Menu.h"
#include "BidirectionalBus.h"
#include "IMenuReactionModel.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace View
        {
            class TagSearchSectionController : private Eegeo::NonCopyable
            {
            private:
                Menu::View::IMenuOptionsModel& m_menuOptionsModel;
                Menu::View::IMenuViewModel& m_menuViewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                const Menu::View::IMenuReactionModel& m_menuReaction;

                Eegeo::Helpers::TCallback1<TagSearchSectionController, const TagSearch::TagSearchAddedMessage&> m_tagSearchAddedMessageHandler;
                Eegeo::Helpers::TCallback1<TagSearchSectionController, const TagSearch::TagSearchRemovedMessage&> m_tagSearchRemovedMessageHandler;

                void OnTagSearchAddedMessage(const TagSearch::TagSearchAddedMessage& message);
                void OnTagSearchRemovedMessage(const TagSearch::TagSearchRemovedMessage& message);
                            
            public:
                TagSearchSectionController(
                        Menu::View::IMenuOptionsModel& menuOptionsModel,
                        Menu::View::IMenuViewModel& menuViewModel,
                        ExampleAppMessaging::TMessageBus& messageBus,
                        const Menu::View::IMenuReactionModel& menuReaction);

                ~TagSearchSectionController();
            };
        }
    }
}
