// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchMenuViewModule.h"

#include "BidirectionalBus.h"
#include "TagSearch.h"
#include "CustomTableDataProvider.h"
#include "Menu.h"
#include "MenuController.h"
#include "Modality.h"
#include "Rendering.h"
#include "SearchMenuController.h"
#include "SearchResultsTableDataProvider.h"
#include "Types.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class SearchMenuViewModule: public ISearchMenuViewModule, private Eegeo::NonCopyable
            {
            private:
                SearchMenuController* m_pController;
                SearchMenuView* m_pView;
                CustomTableDataProvider* m_pDataProvider;
                SearchResultsTableDataProvider* m_pSearchResultsDataProvider;
                
            public:
                SearchMenuViewModule(Menu::View::IMenuModel& searchMenuModel,
                                     Menu::View::IMenuViewModel& searchMenuViewModel,
                                     Menu::View::IMenuSectionViewModel& searchSectionViewModel,
                                     const Eegeo::Rendering::ScreenProperties& screenProperties,
                                     TagSearch::View::ITagSearchRepository& tagSearchRepository,
                                     Modality::View::IModalBackgroundView& modalBackgroundView,
                                     ExampleAppMessaging::TMessageBus& messageBus);
                
                ~SearchMenuViewModule();
                
                Menu::View::MenuController& GetMenuController() const;
                
                SearchMenuView& GetSearchMenuView() const;
            };
        }
    }
}
