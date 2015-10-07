// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "Menu.h"
#include "MenuViewIncludes.h"
#include "IMenuViewModule.h"
#include "Search.h"
#include "CategorySearch.h"
#include "SearchResultMenu.h"
#include "BidirectionalBus.h"
#include "AppModes.h"

#include <string>

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            class SearchMenuViewModule: public Menu::View::IMenuViewModule, private Eegeo::NonCopyable
            {
            private:
                Menu::View::MenuController* m_pController;
                Menu::View::MenuView* m_pView;

            public:
                SearchMenuViewModule(
                    const std::string& viewName,
                    AndroidNativeState& nativeState,
                    Menu::View::IMenuModel& menuModelModel,
                    Menu::View::IMenuViewModel& menuViewModel,
                    CategorySearch::View::ICategorySearchRepository& categorySearchRepository,
                    ISearchResultMenuViewModel& searchResultMenuViewModel,
					Menu::View::IMenuOptionsModel& menuOptionsModel,
					ISearchResultMenuOrder& searchResultMenuOrder,
                    ExampleAppMessaging::TMessageBus& messageBus
                );

                ~SearchMenuViewModule();

                Menu::View::MenuController& GetMenuController() const;
                Menu::View::IMenuView& GetMenuView() const;
            };
        }
    }
}
