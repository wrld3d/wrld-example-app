// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchMenuViewModule.h"

#include "BidirectionalBus.h"
#include "TagSearch.h"
#include "Menu.h"
#include "MenuController.h"
#include "Modality.h"
#include "Rendering.h"
#include "DesktopSearchMenuController.h"
#include "Types.h"
#include "IMenuViewModule.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class SearchMenuViewModule: public Menu::View::IMenuViewModule, private Eegeo::NonCopyable
            {
            private:
                DesktopSearchMenuController* m_pController;
                SearchMenuView* m_pView;
                
            public:
                SearchMenuViewModule(const std::string& viewName,
                                     WindowsNativeState& nativeState,
                                     Menu::View::IMenuModel& searchMenuModel,
                                     Menu::View::IMenuViewModel& searchMenuViewModel,
                                     Menu::View::IMenuSectionViewModel& searchSectionViewModel,
                                     TagSearch::View::ITagSearchRepository& tagSearchRepository,
                                     Modality::View::IModalBackgroundView& modalBackgroundView,
                                     Modality::View::IModalityController& modalityController,
                                     ExampleAppMessaging::TMessageBus& messageBus,
                                     Reaction::View::IReactionModel& reactionModel,
                                     bool isInKioskMode);
                
                ~SearchMenuViewModule();
                
                Menu::View::MenuController& GetMenuController();
                
                Menu::View::IMenuView& GetMenuView();
            };
        }
    }
}
