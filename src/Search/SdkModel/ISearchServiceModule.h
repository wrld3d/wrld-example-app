// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Search.h"
#include "TagSearchModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            class ISearchServiceModule
            {
            public:
                virtual ~ISearchServiceModule() { }
                
                virtual ISearchService& GetSearchService() const = 0;
            };
        }
    }
}
