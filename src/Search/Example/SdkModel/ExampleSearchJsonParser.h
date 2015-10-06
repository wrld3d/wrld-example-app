// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"
#include "ExampleSearchResultModel.h"
#include <string>

namespace ExampleApp
{
    namespace Search
    {
        namespace Example
        {
            namespace SdkModel
            {
                ExampleSearchResultModel TransformToExampleSearchResult(const Search::SdkModel::SearchResultModel& searchResultModel);
                
                bool TryParseImageDetails(const Search::SdkModel::SearchResultModel& searchResultModel, std::string& out_imageUrl);
            }
        }
    }
}