// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <map>
#include "Search.h"
#include "ISearchResultIconKeyMapper.h"
#include "SearchResultModel.h"
#include "Types.h"
#include "SwallowSearchParser.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        class SearchResultIconKeyMapper : public ISearchResultIconKeyMapper, private Eegeo::NonCopyable
        {
        public:
            SearchResultIconKeyMapper();
            ~SearchResultIconKeyMapper();

            ExampleApp::Search::SdkModel::TagIconKey GetIconKeyFromSearchResult(
                    const Search::SdkModel::SearchResultModel& searchResultModel) const;

        private:
            std::map<std::string, std::string> m_availabilityToIconIndex;

            std::string GetMeetingRoomIconFromAvailability(const Search::Swallow::SdkModel::SwallowMeetingRoomResultModel& meetingRoom) const;
       };
    }
}
