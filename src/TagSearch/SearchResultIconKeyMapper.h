// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <map>
#include "Search.h"
#include "ISearchResultIconKeyMapper.h"
#include "SearchResultModel.h"
#include "Types.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        class SearchResultIconKeyMapper : public ISearchResultIconKeyMapper, private Eegeo::NonCopyable
        {
        public:
            ~SearchResultIconKeyMapper();

            ExampleApp::Search::SdkModel::TagIconKey GetIconKeyFromSearchResult(
                    const Search::SdkModel::SearchResultModel& searchResultModel) const;
       };
    }
}
