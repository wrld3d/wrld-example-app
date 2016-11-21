// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultIconKeyMapper.h"
#include "IWorldPinIconMapping.h"
#include "SwallowSearchConstants.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        SearchResultIconKeyMapper::SearchResultIconKeyMapper()
        {
            m_availabilityToIconIndex[Search::Swallow::SearchConstants::MEETING_ROOM_OCCUPIED] = "meeting_room_unavailable";
            m_availabilityToIconIndex[Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE_SOON] = "meeting_room_available_soon";
            m_availabilityToIconIndex[Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE] = "meeting_room_available";
        }

        SearchResultIconKeyMapper::~SearchResultIconKeyMapper()
        {
            
        }
        
        ExampleApp::Search::SdkModel::TagIconKey SearchResultIconKeyMapper::GetIconKeyFromSearchResult(
                const Search::SdkModel::SearchResultModel& searchResultModel) const
        {
            if(searchResultModel.GetPrimaryTag() == Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME)
            {
                const Search::Swallow::SdkModel::SwallowMeetingRoomResultModel& meetingRoom = Search::Swallow::SdkModel::SearchParser::TransformToSwallowMeetingRoomResult(searchResultModel);
                return GetMeetingRoomIconFromAvailability(meetingRoom);
            }

            return searchResultModel.GetIconKey();
        }

        std::string SearchResultIconKeyMapper::GetMeetingRoomIconFromAvailability(const Search::Swallow::SdkModel::SwallowMeetingRoomResultModel& meetingRoom) const
        {
            std::map<std::string, std::string>::const_iterator it = m_availabilityToIconIndex.find(meetingRoom.GetAvailability());

            if (it == m_availabilityToIconIndex.end())
            {
                return "";
            }
            else
            {
                return it->second;
            }
        }
    }
}
