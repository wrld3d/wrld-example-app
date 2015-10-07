// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ISearchResultMenuViewModule.h"
#include "Menu.h"
#include "Search.h"
#include "CategorySearch.h"
#include "Rendering.h"
#include "Modality.h"
#include "SearchResultMenu.h"
#include "SearchResultMenuViewIncludes.h"
#include "BidirectionalBus.h"
#include "SearchResultMenuDataProvider.h"

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
                SearchResultMenuView* m_pView;
                SearchResultMenuDataProvider* m_pDataProvider;

            public:
                SearchResultMenuViewModule(CategorySearch::View::ICategorySearchRepository& categorySearchRepository,
                                           Menu::View::IMenuModel& searchResultMenuModel,
                                           Menu::View::IMenuViewModel& menuViewModel,
                                           ISearchResultMenuViewModel& searchResultMenuViewModel,
                                           Menu::View::IMenuOptionsModel& menuOptionsModel,
                                           ISearchResultMenuOrder& searchResultMenuOrder,
                                           const Eegeo::Rendering::ScreenProperties& screenProperties,
                                           ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchResultMenuViewModule();

                Menu::View::MenuController& GetMenuController() const;

                SearchResultMenuView& GetSearchResultMenuView() const;
            };
        }
    }
}
