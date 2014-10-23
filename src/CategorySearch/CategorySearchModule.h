// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "ICategorySearchModule.h"
#include "Types.h"
#include "Search.h"
#include "Menu.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        class CategorySearchModule : public ICategorySearchModule, private Eegeo::NonCopyable
        {
        public:
            CategorySearchModule(Search::ISearchQueryPerformer& searchQueryPerformer,
                                 ExampleApp::Menu::IMenuViewModel& menuViewModel);
            
            ~CategorySearchModule();
            
            Menu::IMenuModel& GetCategorySearchMenuModel() const;
            
            ICategorySearchRepository& GetCategorySearchRepository() const;
            
        private:
            Menu::IMenuModel* m_pMenuModel;
            Menu::IMenuOptionsModel* m_pMenuOptionsModel;
            ICategorySearchRepository* m_pCategorySearchRepository;
        };
    }
}
