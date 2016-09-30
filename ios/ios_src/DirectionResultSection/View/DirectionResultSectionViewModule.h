// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "DirectionResultSectionController.h"

namespace ExampleApp
{
    namespace DirectionResultSection
    {
        namespace View
        {
            class DirectionResultSectionViewModule : private Eegeo::NonCopyable
            {
            private:
                DirectionResultSectionController* m_pDirectionController;
            public:
                DirectionResultSectionViewModule(Menu::View::IMenuViewModel& directionMenuViewModel,
                                                 Menu::View::IMenuOptionsModel& menuOptionsModel,
                                                 ExampleAppMessaging::TMessageBus& messageBus,
                                                 Menu::View::IMenuReactionModel& menuReaction,
                                                 SearchResultPoi::View::ISearchResultPoiViewModel& searchResultPoiViewModel);
                ~DirectionResultSectionViewModule();
            };
            
        }
    }
}