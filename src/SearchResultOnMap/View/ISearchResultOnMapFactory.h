// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"
#include "SearchResultOnMap.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace View
        {
            class ISearchResultOnMapFactory
            {
            public:
                virtual ~ISearchResultOnMapFactory() { }

                virtual SearchResultOnMapItemModel* CreateSearchResultOnMapItemModel(Search::SdkModel::SearchResultModel& searchResultModel) const = 0;
            };
        }
    }
}
