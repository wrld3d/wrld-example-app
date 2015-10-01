// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SwallowPoiDbConstants.h"

#include "SwallowSearchConstants.h"

using namespace ExampleApp::Search::Swallow::SearchConstants;

namespace ExampleApp
{
    namespace SwallowPoiDb
    {
        namespace Constants
        {
            const std::string EmployeeTableName = "EmployeePois";
            const std::string EmployeeFtsColumnNames[5] = { NAME_FIELD_NAME, JOB_TITLE_FIELD_NAME, WORKING_GROUP_FIELD_NAME, OFFICE_LOCATION_FIELD_NAME, DESK_CODE_FIELD_NAME };
            const float EmployeeFtsColumnWeights[5] = { 1.f, 0.5f, 0.5f, 0.5f, 0.1f };
            
            const std::string MeetingRoomTableName = "MeetingRoomPois";
            const std::string MeetingRoomFtsColumnNames[1] = { NAME_FIELD_NAME };
            const float MeetingRoomFtsColumnWeights[1] = { 1.0f };
            
            const std::string WorkingGroupTableName = "WorkingGroupPois";
            const std::string WorkingGroupFtsColumnNames[2] = { NAME_FIELD_NAME, DESCRIPTION_FIELD_NAME };
            const float WorkingGroupFtsColumnWeights[2] = { 1.0f, 0.5f };
            
            const std::string FacilityTableName = "FacilityPois";
            const std::string FacilityFtsColumnNames[3] = { NAME_FIELD_NAME, CATEGORY_FIELD_NAME, DESCRIPTION_FIELD_NAME };
            const float FacilityFtsColumnWeights[3] = { 1.0f, 1.0f, 0.5f };
            
            const std::string OfficeTableName = "OfficePois";
            const std::string OfficeFtsColumnNames[1] = { NAME_FIELD_NAME };
            const float OfficeFtsColumnWeights[1] = { 1.0f };
        }
    }
}
