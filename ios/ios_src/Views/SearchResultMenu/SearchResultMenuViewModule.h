// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "ISearchResultMenuViewModule.h"
#include "Menu.h"
#include "Search.h"
#include "CategorySearch.h"
#include "Rendering.h"
#include "Modality.h"
#include "SearchResultMenu.h"
#include "UiToNativeMessageBus.h"
#include "NativeToUiMessageBus.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        class SearchResultMenuViewModule: public ISearchResultMenuViewModule, private Eegeo::NonCopyable
        {
        private:
            SearchResultMenuViewController* m_pMenuViewController;
            SearchResultMenuView* m_pView;
            
        public:
            SearchResultMenuViewModule(CategorySearch::ICategorySearchRepository& categorySearchRepository,
                                       Menu::IMenuModel& searchResultMenuModel,
                                       Menu::IMenuViewModel& menuViewModel,
                                       SearchResultMenu::ISearchResultMenuViewModel& searchResultMenuViewModel,
                                       const Eegeo::Rendering::ScreenProperties& screenProperties,
                                       Modality::IModalityModel& modalityModel,
                                       ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
                                       ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);
            
            ~SearchResultMenuViewModule();
            
            MenuViewController& GetSearchResultMenuViewController() const;
            
            SearchResultMenuView& GetSearchResultMenuView() const;
        };
    }
}
