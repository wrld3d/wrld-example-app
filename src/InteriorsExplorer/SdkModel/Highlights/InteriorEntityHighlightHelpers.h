// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"

#include <string>
#include <vector>

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                std::vector<std::string> GetEntityIdsFromSearchResultModel(const Search::SdkModel::SearchResultModel& selectedSearchResult, const std::string& key);
                std::vector<std::string> GetEntityIdsFromSearchResultJson(const std::string& jsonData, const std::string& key);
                std::vector<std::string> GetEntityIdsFromSearchResultJson(const std::string& jsonData);

                std::vector<float> GetHighlightBorderThicknessFromSearchResultModel(const Search::SdkModel::SearchResultModel& selectedSearchResult);
            }
        }
    }
}
