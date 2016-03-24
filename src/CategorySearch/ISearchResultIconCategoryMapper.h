// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"
#include "SwallowSearch.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        class ISearchResultIconCategoryMapper
        {
        public:
            virtual ~ISearchResultIconCategoryMapper() { }
            
            virtual int GetIconIndexFromSearchResult(const Search::SdkModel::SearchResultModel& searchResultModel) const = 0;
            virtual int GetMeetingRoomIconFromAvailability(const Search::Swallow::SdkModel::SwallowMeetingRoomResultModel& meetingRoom) const = 0;

        };
    }
}
