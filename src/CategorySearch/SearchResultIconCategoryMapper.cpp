// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultIconCategoryMapper.h"
#include "SearchResultModel.h"
#include "IWorldPinIconMapping.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        
        SearchResultIconCategoryMapper::~SearchResultIconCategoryMapper()
        {
            
        }
        
        std::string SearchResultIconCategoryMapper::GetIconKeyFromSearchResult(const Search::SdkModel::SearchResultModel& searchResultModel) const
        {
            return searchResultModel.GetCategory();
        }
    }
}
