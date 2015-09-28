// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>

#include "Types.h"

#include "PoiDb.h"
#include "Search.h"
#include "SwallowPersonResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                namespace SearchParser
                {
                    void ParsePersonSearchResults(const std::vector<PoiDb::PoiTableDto>& results,
                                                  std::vector<Search::SdkModel::SearchResultModel>& out_results);
                    
                    SwallowPersonResultModel TransformToSwallowPersonResult(const Search::SdkModel::SearchResultModel& searchResultModel);
                }
            }
        }
    }
}