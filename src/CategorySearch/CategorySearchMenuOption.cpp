// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CategorySearchMenuOption.h"
#include "ISearchQueryPerformer.h"
#include "IMenuViewModel.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        CategorySearchMenuOption::CategorySearchMenuOption(CategorySearchModel model,
                                                           Search::ISearchQueryPerformer& searchQueryPerformer,
                                                           ExampleApp::Menu::IMenuViewModel& menuViewModel)
        : m_model(model)
        , m_searchQueryPerformer(searchQueryPerformer)
        , m_menuViewModel(menuViewModel)
        {
        }
        
        CategorySearchMenuOption::~CategorySearchMenuOption()
        {
            
        }
        
        void CategorySearchMenuOption::Select()
        {
            m_menuViewModel.Close();
            m_searchQueryPerformer.PerformSearchQuery(m_model.SearchCategory(), true);
        }
    }
}
