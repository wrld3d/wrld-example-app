// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultIconKeyMapper.h"
#include "IWorldPinIconMapping.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        SearchResultIconKeyMapper::~SearchResultIconKeyMapper()
        {
            
        }
        
        ExampleApp::Search::SdkModel::TagIconKey SearchResultIconKeyMapper::GetIconKeyFromSearchResult(
                const Search::SdkModel::SearchResultModel& searchResultModel) const
        {
            return searchResultModel.GetIconKey();
        }
    }
}
