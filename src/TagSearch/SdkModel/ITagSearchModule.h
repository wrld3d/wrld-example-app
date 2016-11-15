// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"
#include "TagSearch.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace SdkModel
        {
            class ITagSearchModule
            {
            public:
                virtual ~ITagSearchModule() { }

                virtual Menu::View::IMenuModel& GetTagSearchMenuModel() const = 0;

                virtual Menu::View::IMenuOptionsModel& GetTagSearchMenuOptionsModel() const = 0;

                virtual View::ITagSearchRepository& GetTagSearchRepository() const = 0;
                
                virtual ISearchResultIconKeyMapper& GetSearchResultIconKeyMapper() const = 0;
            };
        }
    }
}
