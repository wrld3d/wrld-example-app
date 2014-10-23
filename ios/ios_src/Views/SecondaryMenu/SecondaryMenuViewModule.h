// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "Menu.h"
#include "ISecondaryMenuViewModule.h"
#include "Rendering.h"
#include "Modality.h"
#include "Search.h"

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        class SecondaryMenuViewModule: public ISecondaryMenuViewModule, private Eegeo::NonCopyable
        {
        private:
            MenuViewController* m_pMenuViewController;
            SearchViewController* m_pSearchViewController;
            SecondaryMenuView* m_pView;
            
        public:
            SecondaryMenuViewModule(Menu::IMenuModel& secondaryMenuModel,
                                    Menu::IMenuViewModel& secondaryMenuViewModel,
                                    const Eegeo::Rendering::ScreenProperties& screenProperties,
                                    Modality::IModalityModel& modalityModel,
                                    Search::ISearchQueryPerformer& searchQueryPerformer,
                                    Search::ISearchService& searchService);
            
            ~SecondaryMenuViewModule();
            
            MenuViewController& GetSecondaryMenuViewController() const;
            
            SecondaryMenuView& GetSecondaryMenuView() const;
        };
    }
}
