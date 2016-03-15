// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultSectionOrder.h"

#include "SearchResultModel.h"
#include "SearchVendorNames.h"
#include "SwallowSearchConstants.h"
#include "SwallowSearchParser.h"
#include "InteriorInteractionModel.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace View
        {
            namespace
            {                
                int GetSwallowResultPriority(const Search::SdkModel::SearchResultModel& result)
                {
                    if(result.GetCategory() == Search::Swallow::SearchConstants::PERSON_CATEGORY_NAME)
                    {
                        return Search::SwallowPeopleVendorPriority;
                    }
                    
                    if(result.GetCategory() == Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME)
                    {
                        return Search::SwallowMeetingRoomsVendorPriority;
                    }
                    
                    if(result.GetCategory() == Search::Swallow::SearchConstants::WORKING_GROUP_CATEGORY_NAME)
                    {
                        return Search::SwallowWorkingGroupsVendorPriority;
                    }
                    
                    if(result.GetCategory() == Search::Swallow::SearchConstants::FACILITY_CATEGORY_NAME)
                    {
                        return Search::SwallowFacilitiesVendorPriority;
                    }
                    
                    if(result.GetCategory() == Search::Swallow::SearchConstants::OFFICE_CATEGORY_NAME)
                    {
                        return Search::SwallowOfficesVendorPriority;
                    }
                    
                    return Search::SwallowVendorPriority_MAX;
                }
                
                int GetAvailabilityPriority(const Search::Swallow::SdkModel::SwallowMeetingRoomResultModel& meetingroom)
                {
                    if(meetingroom.GetAvailability() == Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE)
                    {
                        return Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE_PRIORITY;
                    }
                    else if(meetingroom.GetAvailability() == Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE_SOON)
                    {
                        return Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE_SOON_PRIORITY;
                    }
                    else if(meetingroom.GetAvailability() == Search::Swallow::SearchConstants::MEETING_ROOM_OCCUPIED)
                    {
                        return Search::Swallow::SearchConstants::MEETING_ROOM_OCCUPIED_PRIORITY;
                    }
                    
                    return Search::Swallow::SearchConstants::MEETING_ROOM_MAX_PRIORITY;
                }
                
                bool GetOrderForMeetingRooms(const Search::SdkModel::SearchResultModel& a, const Search::SdkModel::SearchResultModel& b, int currentFloorIndex)
                {
                    // Meeting room order: Current floor first, ordered by Available, Available Soon and Occupied.
                    // Then Lower floor > Higher floor > 2x Lower floor > ...
                    
                    Search::Swallow::SdkModel::SwallowMeetingRoomResultModel roomA = Search::Swallow::SdkModel::SearchParser::TransformToSwallowMeetingRoomResult(a);
                    Search::Swallow::SdkModel::SwallowMeetingRoomResultModel roomB = Search::Swallow::SdkModel::SearchParser::TransformToSwallowMeetingRoomResult(b);
                    
                    if(a.GetFloor() == b.GetFloor())
                    {
                        int meetingRoomAvailabilityValueA = GetAvailabilityPriority(roomA);
                        int meetingRoomAvailabilityValueB = GetAvailabilityPriority(roomB);
                        
                        return meetingRoomAvailabilityValueA < meetingRoomAvailabilityValueB;
                    }
                    else
                    {
                        int floorDistanceA = currentFloorIndex - a.GetFloor();
                        int floorDistanceB = currentFloorIndex - b.GetFloor();
                        
                        int absFloorDistanceA = abs(floorDistanceA);
                        int absFloorDistanceB = abs(floorDistanceB);
                        if(absFloorDistanceA == absFloorDistanceB)
                        {
                            return floorDistanceA > floorDistanceB;
                        }
                        
                        return absFloorDistanceA < absFloorDistanceB;
                    }
                    
                    return false;
                }
            }
            
            SearchResultSectionOrder::SearchResultSectionOrder(const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel)
            : m_interiorInteractionModel(interiorInteractionModel)
            {
                
            }
            
            bool SearchResultSectionOrder::operator() (const Search::SdkModel::SearchResultModel& a, const Search::SdkModel::SearchResultModel& b)
            {
                //Order eeGeo results on top
                if(a.GetVendor() != b.GetVendor() && a.GetVendor() == Search::EegeoVendorName)
                {
                    return true;
                }
                //Order GeoNames results as they came in
                if(a.GetVendor() == Search::GeoNamesVendorName || b.GetVendor() == Search::GeoNamesVendorName)
                {
                    return false;
                }
                //Order eeGeo results as they came in
                if(a.GetVendor() == Search::EegeoVendorName || b.GetVendor() == Search::EegeoVendorName)
                {
                    if (a.GetCategory() == b.GetCategory())
                    {
                        if(a.GetCategory() == Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME &&
                           a.GetVendor() == Search::EegeoVendorName &&
                           b.GetVendor() == Search::EegeoVendorName)
                        {
                            return GetOrderForMeetingRooms(a, b, m_interiorInteractionModel.GetSelectedFloorIndex());
                        }
                        
                        return false;
                    }
                    else
                    {
                        int aPriority = GetSwallowResultPriority(a);
                        int bPriority = GetSwallowResultPriority(b);
                        return aPriority < bPriority;
                    }
                }
                return a < b;
            }
            
            
        }
    }
}