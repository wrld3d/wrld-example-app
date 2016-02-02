// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WindowsNativeState.h"
#include "Types.h"
#include "Menu.h"
#include "MenuViewIncludes.h"
#include "IMenuViewModule.h"
#include "Search.h"
#include "CategorySearch.h"
//#include "SearchResultMenu.h"
#include "BidirectionalBus.h"
#include "AppModes.h"

#include <string>

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class SearchMenuViewModule : public Menu::View::IMenuViewModule, private Eegeo::NonCopyable
            {
            private:
                Menu::View::MenuController* m_pController;
                Menu::View::MenuView* m_pView;

            public:
                SearchMenuViewModule(
                    const std::string& viewName,
                    WindowsNativeState& nativeState,
                    Menu::View::IMenuModel& searchMenuModel,
                    Menu::View::IMenuViewModel& searchMenuViewModel,
                    Menu::View::IMenuSectionViewModel& searchSectionViewModel,
                    CategorySearch::View::ICategorySearchRepository& categorySearchRepository,
                    Modality::View::IModalBackgroundView& modalBackgroundView,
                    ExampleAppMessaging::TMessageBus& messageBus
                    );

                ~SearchMenuViewModule();

                Menu::View::MenuController& GetMenuController();
                Menu::View::IMenuView& GetMenuView();
            };
        }
    }
}