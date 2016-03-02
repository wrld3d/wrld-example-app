// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultSectionOrder.h"

#include "SearchResultModel.h"
#include "SearchVendorNames.h"
#include "SwallowSearchConstants.h"

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