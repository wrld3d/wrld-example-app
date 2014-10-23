// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMenuOption.h"
#include "CategorySearchModel.h"
#include "Search.h"
#include "Menu.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        class CategorySearchMenuOption : public Menu::IMenuOption
        {
            CategorySearchModel m_model;
            Search::ISearchQueryPerformer& m_searchQueryPerformer;
            ExampleApp::Menu::IMenuViewModel& m_menuViewModel;
            
        public:
            CategorySearchMenuOption(CategorySearchModel model,
                                     Search::ISearchQueryPerformer& searchQueryPerformer,
                                     ExampleApp::Menu::IMenuViewModel& menuViewModel);
            
            ~CategorySearchMenuOption();
            
            void Select();
        };
    }
}
