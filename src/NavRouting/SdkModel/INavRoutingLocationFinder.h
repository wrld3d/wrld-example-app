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
                virtual ~INavRoutingLocationFinder() {};

                virtual bool TryGetCurrentLocation(NavRoutingLocationModel &outLocation) = 0;

                virtual bool TryGetLocationFromSearchNavigationData(
                        const SearchNavigationData &searchNavigationData,
                        NavRoutingLocationModel &outLocation) = 0;
                
                virtual void FailedToFindLocationMessage() = 0;
            };
        }
    }
}
