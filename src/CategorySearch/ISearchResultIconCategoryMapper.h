// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        class ISearchResultIconCategoryMapper
        {
        public:
            virtual ~ISearchResultIconCategoryMapper() { }
            
            virtual std::string GetIconKeyFromSearchResult(const Search::SdkModel::SearchResultModel& searchResultModel) const = 0;
        };
    }
}
