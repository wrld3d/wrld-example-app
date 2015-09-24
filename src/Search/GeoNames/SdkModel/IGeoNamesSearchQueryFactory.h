// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"
#include "ICallback.h"
#include "IGeoNamesSearchQuery.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            namespace SdkModel
            {
                class IGeoNamesSearchQueryFactory
                {
                public:
                    virtual ~IGeoNamesSearchQueryFactory() { }
                    
                    virtual IGeoNamesSearchQuery* CreateGeoNamesSearchForQuery(const Search::SdkModel::SearchQuery& query,
                                                                               Eegeo::Helpers::ICallback0& completionCallback) = 0;
                };
            }
        }
    }
}
