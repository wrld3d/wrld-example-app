// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowSearchResultMenuOrder.h"

#include "SearchResultModel.h"
#include "SearchVendorNames.h"
#include "SwallowSearchConstants.h"
#include "SwallowSearchParser.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            namespace Swallow
            {
                int GetSwallowResultPriority(const Search::SdkModel::SearchResultModel& result)
                {
                    if(result.GetVendor() == Search::SwallowPeopleVendorName)
                    {
                        return Search::SwallowPeopleVendorPriority;
                    }
                    
                    if(result.GetVendor() == Search::SwallowMeetingRoomsVendorName)
                    {
                        return Search::SwallowMeetingRoomsVendorPriority;
                    }
                    
                    if(result.GetVendor() == Search::SwallowWorkingGroupsVendorName)
                    {
                        return Search::SwallowWorkingGroupsVendorPriority;
                    }
                    
                    if(result.GetVendor() == Search::SwallowFacilitiesVendorName)
                    {
                        return Search::SwallowFacilitiesVendorPriority;
                    }
                    
                    if(result.GetVendor() == Search::SwallowOfficesVendorName)
                    {
                        return Search::SwallowOfficesVendorPriority;
                    }
                    
                    return Search::SwallowVendorPriority_MAX;
                }
                
                int GetMeetingRoomAvailabilityPriority(const std::string& availability)
                {
                    if(availability == Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE)
                    {
                        return Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE_PRIORITY;
                    }
                    
                    if(availability == Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE_SOON)
                    {
                        return Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE_SOON_PRIORITY;
                    }
                    
                    if(availability == Search::Swallow::SearchConstants::MEETING_ROOM_OCCUPIED)
                    {
                        return Search::Swallow::SearchConstants::MEETING_ROOM_OCCUPIED_PRIORITY;
                    }
                    
                    return Search::Swallow::SearchConstants::MEETING_ROOM_MAX_PRIORITY;
                }
                
                std::string GetSurname(const std::string& name)
                {
                    size_t lastSpacePos = name.find_last_of(" ");
                    
                    if(lastSpacePos == std::string::npos || lastSpacePos == name.size() - 1)
                    {
                        return name;
                    }
                    
                    return name.substr(lastSpacePos + 1);
                }
                
                bool SwallowSubCategorySort(int priority, const Search::SdkModel::SearchResultModel& a, const Search::SdkModel::SearchResultModel& b)
                {
                    if(priority == Search::SwallowPeopleVendorPriority)
                    {
                        // presumably at some point we will store the surname separately, this function should suffice in the meantime
                        std::string aSurname = GetSurname(a.GetTitle());
                        std::string bSurname = GetSurname(b.GetTitle());
                        
                        if(aSurname != bSurname)
                        {
                            return aSurname < bSurname;
                        }
                    }
                    
                    if(priority == Search::SwallowMeetingRoomsVendorPriority)
                    {
                        const Search::Swallow::SdkModel::SwallowMeetingRoomResultModel& aMeetingRoomResult = Search::Swallow::SdkModel::SearchParser::TransformToSwallowMeetingRoomResult(a);
                        
                        const Search::Swallow::SdkModel::SwallowMeetingRoomResultModel& bMeetingRoomResult = Search::Swallow::SdkModel::SearchParser::TransformToSwallowMeetingRoomResult(b);
                        
                        int aPriority = GetMeetingRoomAvailabilityPriority(aMeetingRoomResult.GetAvailability());
                        int bPriority = GetMeetingRoomAvailabilityPriority(bMeetingRoomResult.GetAvailability());
                        
                        if(aPriority != bPriority)
                        {
                            return aPriority < bPriority;
                        }
                    }
                    
                    return a.GetTitle() < b.GetTitle();
                }
                
                bool SwallowSearchResultMenuOrder::operator() (const Search::SdkModel::SearchResultModel& a, const Search::SdkModel::SearchResultModel& b)
                {
                    bool aIsSwallowResult = a.GetVendor().find(Search::SwallowVendorName) != std::string::npos;
                    bool bIsSwallowResult = b.GetVendor().find(Search::SwallowVendorName) != std::string::npos;
                    
                    if(aIsSwallowResult && !bIsSwallowResult)
                    {
                        return true;
                    }
                    
                    if(!aIsSwallowResult && bIsSwallowResult)
                    {
                        return false;
                    }
                    
                    if(aIsSwallowResult && bIsSwallowResult)
                    {
                        int aPriority = GetSwallowResultPriority(a);
                        int bPriority = GetSwallowResultPriority(b);
                        
                        if(aPriority != bPriority)
                        {
                            return aPriority < bPriority;
                        }
                        else
                        {
                            return SwallowSubCategorySort(aPriority, a, b);
                        }
                    }
                    
                    //GeoNames results on top
                    if(a.GetVendor() != b.GetVendor() && a.GetVendor() == Search::GeoNamesVendorName)
                    {
                            return true;
                    }
                    //Order GeoNames results as they came in
                    if(a.GetVendor() == Search::GeoNamesVendorName || b.GetVendor() == Search::GeoNamesVendorName)
                    {
                        return false;
                    }
                    return a < b;
                }
            }
        }
    }
}