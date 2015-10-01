// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowSearchResultMenuOrder.h"

#include "SearchResultModel.h"
#include "SearchVendorNames.h"

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
                        
                        return aPriority < bPriority;
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