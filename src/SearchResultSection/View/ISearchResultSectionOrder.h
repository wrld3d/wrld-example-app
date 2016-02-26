// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace View
        {
            class ISearchResultSectionOrder
            {
            public:
                virtual ~ISearchResultSectionOrder(){};
                
                // This operator should return true if a should come before b
                // (if indifferent return false and the relative order will be maintained)
                virtual bool operator() (const Search::SdkModel::SearchResultModel& a, const Search::SdkModel::SearchResultModel& b) = 0;
            };
        }
    }
}
