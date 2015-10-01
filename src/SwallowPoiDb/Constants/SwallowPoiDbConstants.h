// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace SwallowPoiDb
    {
        namespace Constants
        {
            extern const std::string EmployeeTableName;
            extern const std::string EmployeeFtsColumnNames[5];
            extern const float EmployeeFtsColumnWeights[5];
            
            extern const std::string MeetingRoomTableName;
            extern const std::string MeetingRoomFtsColumnNames[1];
            extern const float MeetingRoomFtsColumnWeights[1];
            
            extern const std::string WorkingGroupTableName;
            extern const std::string WorkingGroupFtsColumnNames[2];
            extern const float WorkingGroupFtsColumnWeights[2];
            
            extern const std::string FacilityTableName;
            extern const std::string FacilityFtsColumnNames[3];
            extern const float FacilityFtsColumnWeights[3];
            
            extern const std::string OfficeTableName;
            extern const std::string OfficeFtsColumnNames[1];
            extern const float OfficeFtsColumnWeights[1];
        }
    }
}