// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <map>
#include "Search.h"
#include "ISearchResultIconCategoryMapper.h"
#include "Types.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        class SearchResultIconCategoryMapper : public ISearchResultIconCategoryMapper, private Eegeo::NonCopyable
        {
            std::map<std::string, int> m_categoryToIconIndex;
            
        public:
            SearchResultIconCategoryMapper();
            
            ~SearchResultIconCategoryMapper();
            
            int GetIconIndexFromSearchResult(const Search::SdkModel::SearchResultModel& searchResultModel) const;
        };
    }
}
