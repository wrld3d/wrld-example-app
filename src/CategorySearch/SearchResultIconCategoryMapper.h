// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <map>
#include "Search.h"
#include "ISearchResultIconCategoryMapper.h"
#include "Types.h"
#include "SwallowMeetingRoomResultModel.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        class SearchResultIconCategoryMapper : public ISearchResultIconCategoryMapper, private Eegeo::NonCopyable
        {
            std::map<std::string, int> m_categoryToIconIndex;
            std::map<std::string, int> m_availabilityToIconIndex;
            
        public:
            SearchResultIconCategoryMapper();
            
            ~SearchResultIconCategoryMapper();
            
            int GetIconIndexFromSearchResult(const Search::SdkModel::SearchResultModel& searchResultModel) const;
            
            int GetMeetingRoomIconFromAvailability(const Search::Swallow::SdkModel::SwallowMeetingRoomResultModel& meetingRoom) const;
        };
    }
}
