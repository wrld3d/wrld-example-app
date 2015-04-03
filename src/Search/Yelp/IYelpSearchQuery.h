// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Search.h"
#include <vector>
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            class IYelpSearchQuery
            {
            public:
                virtual ~IYelpSearchQuery() { }
                
                virtual void Dispatch() = 0;
                
                virtual void Cancel() = 0;
                
                virtual bool IsSucceeded() = 0;
                
                virtual const std::string& ResponseString() = 0;
                virtual const std::vector<SdkModel::SearchResultModel>& ResponseSearchQueryResults() = 0;
            };
        }
    }
}
