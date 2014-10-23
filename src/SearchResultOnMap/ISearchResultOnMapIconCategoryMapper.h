// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Search.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        class ISearchResultOnMapIconCategoryMapper
        {
        public:
            virtual ~ISearchResultOnMapIconCategoryMapper() { }
            
            virtual int GetIconIndexFromSearchResult(const Search::SearchResultModel& searchResultModel) const = 0;
        };
    }
}
