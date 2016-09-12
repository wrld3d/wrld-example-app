// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace CategorySearch
    {
        namespace View
        {
            class ICategorySearchModel;
            class ICategorySearchRepository;
            class CategorySearchMenuOption;
            
            class CategorySearchMenuModel : public Menu::View::MenuModel
            {
            };
            
            class CategorySearchMenuOptionsModel : public Menu::View::MenuOptionsModel
            {
            public:
                CategorySearchMenuOptionsModel(const std::shared_ptr<CategorySearchMenuModel>& categorySearch) : Menu::View::MenuOptionsModel(*categorySearch)
                {
                }
            };
        }
        
        class ISearchResultIconCategoryMapper;        
    }
}
