// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"
#include "CategorySearch.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        namespace SdkModel
        {
            class ICategorySearchModule
            {
            public:
                virtual ~ICategorySearchModule() { }

                virtual Menu::View::IMenuModel& GetCategorySearchMenuModel() const = 0;

                virtual View::ICategorySearchRepository& GetCategorySearchRepository() const = 0;
            };
        }
    }
}
