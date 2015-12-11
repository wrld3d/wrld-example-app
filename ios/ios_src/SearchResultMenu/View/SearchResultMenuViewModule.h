// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchResultMenuViewModule.h"

#include "BidirectionalBus.h"
#include "CategorySearch.h"
#include "Menu.h"
#include "SearchResultMenu.h"
#include "SearchResultMenuViewIncludes.h"
#include "Types.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            class SearchResultMenuViewModule: public ISearchResultMenuViewModule, private Eegeo::NonCopyable
            {
            private:
                SearchResultMenuController* m_pController;
                SearchResultMenuDataProvider* m_pDataProvider;

            public:
                SearchResultMenuViewModule(CategorySearch::View::ICategorySearchRepository& categorySearchRepository,
                                           Menu::View::IMenuViewModel& searchMenuViewModel,
                                           Menu::View::IMenuOptionsModel& menuOptionsModel,
                                           ISearchResultMenuOrder& searchResultMenuOrder,
                                           ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchResultMenuViewModule();
            };
        }
    }
}
