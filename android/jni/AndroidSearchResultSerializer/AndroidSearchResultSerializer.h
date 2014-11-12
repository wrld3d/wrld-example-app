// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include <string>
#include "SearchResultModel.h"

namespace ExampleApp
{
namespace AndroidSearchResultSerializer
{
std::string SerializeSearchResult(const Search::SearchResultModel& searchResult);

Search::SearchResultModel DeserializeSearchResult(const std::string& searchResult);
}
}
