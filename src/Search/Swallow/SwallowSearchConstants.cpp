// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowSearchConstants.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            const std::string JOB_TITLE_FIELD_NAME = "jobTitle";
            const std::string WORKING_GROUP_FIELD_NAME = "workingGroup";
            const std::string OFFICE_LOCATION_FIELD_NAME = "officeLocation";
            const std::string DESK_CODE_FIELD_NAME = "deskCode";
            
            std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels()
            {
                std::vector<ExampleApp::CategorySearch::View::CategorySearchModel> categories;
                categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Meeting Rooms", "meeting_rooms", "meeting_rooms"));
                categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Working Groups", "working_groups", "working_groups"));
                categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Facilities", "facilities", "facilities"));
                categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Offices", "offices", "offices"));
                return categories;
            }
        }
    }
}