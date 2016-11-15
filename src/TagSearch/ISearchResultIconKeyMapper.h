// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        class ISearchResultIconKeyMapper
        {
        public:
            virtual ~ISearchResultIconKeyMapper() { }
            
            virtual ExampleApp::Search::SdkModel::TagIconKey GetIconKeyFromSearchResult(
                    const Search::SdkModel::SearchResultModel& searchResultModel) const = 0;
        };
    }
}
