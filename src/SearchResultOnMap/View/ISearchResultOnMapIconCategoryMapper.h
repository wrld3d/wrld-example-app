// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace View
        {
            class ISearchResultOnMapIconCategoryMapper
            {
            public:
                virtual ~ISearchResultOnMapIconCategoryMapper() { }

                virtual int GetIconIndexFromSearchResult(const Search::SdkModel::SearchResultModel& searchResultModel) const = 0;
            };
        }
    }
}
