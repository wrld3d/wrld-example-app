// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace Search
    {
        extern const std::string YelpVendorName;
        extern const std::string GeoNamesVendorName;
	    extern const std::string ExampleTourVendorName;
        extern const std::string EegeoVendorName;
        
        enum SwallowVendorPriority
        {
            SwallowPeopleVendorPriority = 0,
            SwallowMeetingRoomsVendorPriority,
            SwallowWorkingGroupsVendorPriority,
            SwallowFacilitiesVendorPriority,
            SwallowDepartmentsVendorPriority,
            SwallowOfficesVendorPriority,
            SwallowVendorPriority_MAX
        };
		
        extern const std::string ExampleTourVendorName;
        
        extern const std::string InteriorVendorName;
        extern const std::string WorldTwitterVendorName;
        extern const std::string TourTwitterVendorName;
        extern const std::string MyPinVendorName;
    }
}
