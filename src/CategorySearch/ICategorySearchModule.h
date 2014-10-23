// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Menu.h"
#include "CategorySearch.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        class ICategorySearchModule
        {
        public:
            virtual ~ICategorySearchModule() { }
            
            virtual Menu::IMenuModel& GetCategorySearchMenuModel() const = 0;
            
            virtual ICategorySearchRepository& GetCategorySearchRepository() const = 0;
        };
    }
}
