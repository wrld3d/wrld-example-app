// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchResultSectionViewModule.h"

#include "BidirectionalBus.h"
#include "Menu.h"
#include "SearchResultSection.h"
#include "Types.h"
#include "IMenuReactionModel.h"
#include "SearchResultPoi.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace View
        {
            class SearchResultSectionViewModule: public ISearchResultSectionViewModule, private Eegeo::NonCopyable
            {
            private:
                SearchResultSectionController* m_pController;

            public:
                SearchResultSectionViewModule(Menu::View::IMenuViewModel& searchMenuViewModel,
                                              Menu::View::IMenuOptionsModel& menuOptionsModel,
                                              ISearchResultSectionOrder& searchResultSectionOrder,
                                              ExampleAppMessaging::TMessageBus& messageBus,
                                              Menu::View::IMenuReactionModel& menuReaction,
                                              SearchResultPoi::View::ISearchResultPoiViewModel& searchResultPoiViewModel);

                ~SearchResultSectionViewModule();
            };
        }
    }
}
