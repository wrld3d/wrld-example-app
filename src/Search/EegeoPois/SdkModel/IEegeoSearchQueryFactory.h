// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Search.h"
#include "ICallback.h"
#include "IEegeoSearchQuery.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                class IEegeoSearchQueryFactory
                {
                public:
                    virtual ~IEegeoSearchQueryFactory() { }
                    
                    virtual IEegeoSearchQuery* CreateEegeoSearchForQuery(const Search::SdkModel::SearchQuery& query,
                                                                                 Eegeo::Helpers::ICallback0& completionCallback) = 0;
                };
            }
        }
    }
}
