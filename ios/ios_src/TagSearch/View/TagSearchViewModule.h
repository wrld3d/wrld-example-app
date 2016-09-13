// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ITagSearchViewModule.h"
#include "Types.h"
#include "TagSearch.h"
#include "IMenuOptionsModel.h"
#include "BidirectionalBus.h"
#include "IMenuReactionModel.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace View
        {
            class TagSearchViewModule : public ITagSearchViewModule, private Eegeo::NonCopyable
            {
            private:
                TagSearch::View::TagSearchSectionController* m_pController;

            public:
                static TagSearchViewModule* Create(
                        Menu::View::IMenuOptionsModel& menuOptionsModel,
                        Menu::View::IMenuViewModel& menuViewModel,
                        ExampleAppMessaging::TMessageBus& messageBus,
                        const ExampleApp::Menu::View::IMenuReactionModel& menuReaction);

                TagSearchViewModule(TagSearch::View::TagSearchSectionController* pController);
                ~TagSearchViewModule();
            };
        }
    }
}
