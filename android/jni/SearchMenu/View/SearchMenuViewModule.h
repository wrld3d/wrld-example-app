// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "Menu.h"
#include "MenuViewIncludes.h"
#include "IMenuViewModule.h"
#include "Search.h"
#include "TagSearch.h"
#include "SearchMenu.h"
#include "BidirectionalBus.h"
#include "AppModes.h"
#include "Modality.h"

#include <string>

namespace ExampleApp
{
    namespace SearchMenu
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
                    Menu::View::IMenuSectionViewModel& searchSectionViewModel,
                    TagSearch::View::ITagSearchRepository& tagSearchRepository,
					Menu::View::IMenuOptionsModel& menuOptionsModel,
                    Modality::View::IModalBackgroundView& modalBackgroundView,
                    ExampleAppMessaging::TMessageBus& messageBus
                );

                ~SearchMenuViewModule();

                Menu::View::MenuController& GetMenuController() const;
                Menu::View::IMenuView& GetMenuView() const;
            };
        }
    }
}
