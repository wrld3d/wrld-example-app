#pragma once

#include "NavRouting.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class INavRoutingLocationFinder
            {
            public:
                virtual bool TryGetCurrentLocation(NavRoutingLocationModel &outLocation) = 0;
                virtual bool TryGetLocationFromSearchResultModel(
                        const Search::SdkModel::SearchResultModel& searchResultModel,
                        NavRoutingLocationModel &outLocation) = 0;
            };
        }
    }
}
